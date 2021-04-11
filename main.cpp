#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const int TOTALSTOCKS = 10;

class Stock
{
private:

    double Stock_Issue_Price;//股票發行價
    double Stock_Listed_Price;//股票上市價
    double Market_Value;//市值
    string Stock_Name;//股票名稱
    string Stock_Code;//股票代碼
    bool Hang;//是否掛起
    long long int Number_Of_Listed_Stocks;//上市股票數
    long long int Free_Stocks_Float;//自由流通股份
    long long int The_Share_Volume_Of_Stocks;//股票成交量

public:
    Stock()
    {
        Stock_Issue_Price = 0;
        Stock_Listed_Price = 0;
        Market_Value = 0;
        Stock_Name = "";
        Stock_Code = "";
        Hang = true;
        Number_Of_Listed_Stocks = 0;
        Free_Stocks_Float = 0;
        The_Share_Volume_Of_Stocks = 0;
    }

    void Add_New_Stock();//加入新股票(管理員)
    void Delete_Stock();//刪除股票(管理員)
    void Modify_Stock();//修改股票資料(管理員)
    void Display_Stock_Market_Information();
    /*展示各項股市信息
    (
    1.開盤價：Opening Price
    2.收盤價：Closing Price
    3.漲停：Limit Up
    4.跌停：Limit Down
    5.買價：Bid Price
    6.賣價：Ask Price / Offer Price
    ......等
    )
    */
    void Hang_Up_Stock();//掛起股票
    void Un_Hang_Stock();//解掛股票
    void Write_File(vector <Stock>);//寫檔(每次執行完存檔)
    void setEverything(double, double, double, string, string, bool, long long, long long, long long);

}Enter[TOTALSTOCKS];

void Stock::Write_File(vector <Stock> data)
{
    ofstream stockData;
    stockData.open("stockData.txt");
    if (!stockData)
    {
        cout << "無法開啟\"stockData.txt\"" << endl;
    }

    int vectorLen = data.size();

    for (int i=0; i<vectorLen; i++)
    {
        stockData << data[i].Stock_Issue_Price << ' ' << data[i].Stock_Listed_Price << ' ' << data[i].Market_Value << ' '
        << data[i].Stock_Name << ' ' << data[i].Stock_Code << ' ' << data[i].Hang << ' ' << data[i].Number_Of_Listed_Stocks << ' '
        << data[i].Free_Stocks_Float << ' ' << data[i].The_Share_Volume_Of_Stocks << endl;
    }
}

void Stock::setEverything(double issue, double listed, double market, string name, string code, bool hang, long long lisedNumber, long long floatStock, long long shareVolume)
{
    this->Stock_Issue_Price = issue;
    this->Stock_Listed_Price = listed;
    this->Market_Value = market;
    this->Stock_Name = name;
    this->Stock_Code = code;
    this->Hang = hang;
    this->Number_Of_Listed_Stocks = lisedNumber;
    this->Free_Stocks_Float = floatStock;
    this->The_Share_Volume_Of_Stocks = shareVolume;
}
// class Customer
// {
// private:
//     string Customer_Name[elements];//用戶名
//     string Customer_Password[elements];//密碼
//     long long int Holding_Stock_Numbers[elements];//持有股票數量
//     string Holding_Stock_Name[elements];//持有股票名稱
//     string Holding_Stock_code[elements];//持有股票代碼
//     double Balance;//現金餘額
//     double Total_Assets;//總資產
//     bool Administrator;//是否為管理員

// public:
//     void Log_In();//登錄
//     void Register();//註冊

// };

class UI
{
public:
    void Menu();//選擇菜單
};

int main()
{
    double issuePrice, listedPrice, marketValue;//發行價 上市價 市值
    string name, code;//名子 代碼
    bool hang;//掛起
    long long listedNumber, shareVolume, floatNumber;//上市股票數 股票成交量 自由流通股份

    ifstream stockData;
    stockData.open("stockData.txt");
    if (!stockData)
    {
        cout << "無法開啟\"stockData.txt\"" << endl;
    }

    for (int i=0; i<TOTALSTOCKS; i++)//讀檔
    {
        stockData >> issuePrice >> listedPrice >> marketValue >> name >> code >> hang >> listedNumber >> floatNumber >> shareVolume;
        Enter[i].setEverything(issuePrice, listedPrice, marketValue, name, code, hang, listedNumber, floatNumber, shareVolume);
    }
    stockData.close();
    
}