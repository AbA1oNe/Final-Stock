#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
//股票刷新則updateTimes++,並且寫檔再重新讀檔

using namespace std;

const int TOTALSTOCKS = 10;//設定有放幾個股票的資料
const string STOCKNAME[TOTALSTOCKS] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};//TOTALSTOCKS個股票資料的txt檔案

class Stock
{
private:
    string Stock_Name;//股票名稱
    string Stock_Code;//股票代碼
    int updateTimes;//更新次數, 未來折線圖使用
    double Stock_Issue_Price;//股票發行價
    double Stock_Listed_Price;//股票上市價
    double Market_Value;//市值
    long long int Free_Stocks_Float;//自由流通股份
    long long int The_Share_Volume_Of_Stocks;//股票成交量
    double openingPrice;//開盤價
    double closingPrice;//收盤價
    double currentPrice;//買賣價

public:
    Stock()
    {
        Stock_Name = "";
        Stock_Code = "";
        updateTimes = 0;
        Stock_Issue_Price = 0;
        Stock_Listed_Price = 0;
        Market_Value = 0;
        Free_Stocks_Float = 0;
        The_Share_Volume_Of_Stocks = 0;
        openingPrice = 0;
        closingPrice = 0;
        currentPrice = 0;
    }

    void setEverything(string, string, int, double, double, double, long long, long long, long long, long long, long long);
    void Add_New_Stock();//加入新股票(管理員)
    void Delete_Stock();//刪除股票(管理員)
    void Modify_Stock();//修改股票資料(管理員)
    friend void Display_Stock_Market_Information(int );//receive option number+1 if -1, then it's display all info
    /*展示各項股市信息
    (
    1.開盤價：Opening Price
    2.收盤價：Closing Price
    3.漲停：Limit Up
    4.跌停：Limit Down
    5.價格 : Price
    ......等
    )
    */
    friend void Write_File();//寫檔
                            //以下為拿private data
    string getStock_Name();
    string getStock_Code();
    int getUpdateTimes();
    double getStock_Issue_Price();
    double getStock_Listed_Price();
    double getMarket_Value();
    long long int getFree_Stocks_Float();
    long long int getThe_Share_Volume_Of_Stocks();
    double getOpeningPrice();
    double getClosingPrice();
    double getPrice();

    bool checkFloat();//檢查浮動 如果漲則true
    double randomChange();//隨時間改變目前的價格

}Enterprise[TOTALSTOCKS];

void Stock::setEverything(string name, string code, int update, double issue, double listed, double market, long long floatStock, long long shareVolume, long long opening, long long closing, long long current)
{   //設定class的private data
    this->Stock_Name = name;
    this->Stock_Code = code;
    this->updateTimes = update;
    this->Stock_Issue_Price = issue;
    this->Stock_Listed_Price = listed;
    this->Market_Value = market;
    this->Free_Stocks_Float = floatStock;
    this->The_Share_Volume_Of_Stocks = shareVolume;
    this->openingPrice = opening;
    this->closingPrice = closing;
    this->currentPrice = current;
}

string Stock::getStock_Name()
{
    return this->Stock_Name;
}

class Customer
{
private:
    string Customer_Name;//用戶名
    string Customer_Password;//密碼
    struct holdingStock
    {
        long long holdingNumbers;//持有股票數量
        string Holding_Stock_Name;//持有股票名稱
        string Holding_Stock_code;//持有股票代碼
        double StockPrice;//該股票買進的價格
    };
    double Balance;//現金餘額
    double Total_Assets;//總資產
    bool Administrator;//是否為管理員

public:
    void Log_In();//登錄
    void Register();//註冊
    void buy();//買
    void sell();//賣
    string getName();
    string getPass();
    holdingStock getHoldingStock();
    double getBalance();
    double getTotalAsset();
    bool getAdmin();
};

void Write_File()//因為未來預計要做折線圖，所以用ios::app讓每一次的更新都可以被記錄下來
{
    ofstream stockData;
    for (int i=0; i<TOTALSTOCKS; i++)
    {
        stockData.open("stockData" + STOCKNAME[i] + ".txt", ios::app);
        if (!stockData)
        {
            cout <<"Unable to open: "<< "stockData" << STOCKNAME[i] << endl;
        }
        else {
            stockData << Enterprise[i].Stock_Name << ' ' << Enterprise[i].Stock_Code << ' ' << Enterprise[i].updateTimes <<
            ' ' << Enterprise[i].Stock_Issue_Price << ' ' << Enterprise[i].Stock_Listed_Price << ' ' << Enterprise[i].Market_Value <<
            ' ' << ' ' << Enterprise[i].Free_Stocks_Float <<
            ' ' << Enterprise[i].The_Share_Volume_Of_Stocks <<
            ' ' << Enterprise[i].openingPrice << ' ' << Enterprise[i].closingPrice << ' ' <<
            ' ' << Enterprise[i].currentPrice <<endl;
        }
        stockData.close();
    }
}

void readFile()
{
    int update;//更新次數
    double issuePrice, listedPrice, marketValue, opening, closing, current;//發行價 上市價 市值 開盤 收盤 買賣價
    string name, code;//名子 代碼
    long long floatNumber, shareVolume;// 股票成交量 自由流通股份

    ifstream stockData;
    for (int i=0; i<TOTALSTOCKS; i++)
    {
        stockData.open("stockData" + STOCKNAME[i] + ".txt");
        if (!stockData)
        {
            cout <<"Unable to open: "<< "stockData" << STOCKNAME[i] << endl;
        }
        else {
            while (stockData >> name)//反覆讀入直到讀到最後(最新)的一行資料
            {
                stockData >> code >> update >> issuePrice >> listedPrice >> marketValue >> floatNumber >> shareVolume >> opening >> closing >> current;
            }
            Enterprise[i].setEverything(name, code, update, issuePrice, listedPrice, marketValue, floatNumber, shareVolume, opening, closing, current);
        }
        stockData.close();
    }
}

void Display_Stock_Market_Information(int opt)
{
    if (opt == -1)//all info
    {
        cout << "股票名稱/代碼" << " 股票發行價 股票上市價 市值 流通股份量 成交量 開盤價 收盤價 目前買賣價格" << endl;
        cout << "------------------------------------------------------------------------------------" << endl << endl;
        for (int i=0; i<TOTALSTOCKS; i++)
        {
            cout << i+1 << ". ";
            cout << Enterprise[i].Stock_Name << "  " << Enterprise[i].Stock_Code << " " << Enterprise[i].Stock_Issue_Price << "         " << Enterprise[i].Stock_Listed_Price << "\t    "
                 << Enterprise[i].Market_Value << "  " << Enterprise[i].Free_Stocks_Float << "        " << Enterprise[i].The_Share_Volume_Of_Stocks << "    "
                 << Enterprise[i].openingPrice << "     " << Enterprise[i].closingPrice << "     " << Enterprise[i].currentPrice << endl;
        }

    }
}

void menu()
{
    int option;
    cout << "請輸入選項號碼" << endl;
    cout << "---------------------------" << endl;
    cout << "1.顯示所有股票資訊" << endl;
    cout << "2.顯示特定股票資訊" << endl;
    cout << "---------------------------" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        Display_Stock_Market_Information(-1);
        break;

    default:
        break;
    }
}


int main()
{
    readFile();
    menu();
}
