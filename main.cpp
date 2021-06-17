#include <iostream>
#include <cstring>
#include <conio.h>//getch()
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#include <cstdlib>
//#define TOTALSTOCKS 5
using namespace std;

const int TOTALSTOCKS = 10;//設定有放幾個股票的資料
//int Num_Of_Stock;//現有股票種類數量，計數用
int flag;
int getTime();      //股票浮動之一Function
double Random();    //股票浮動之一Function

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Stock_Volume;    //股票總股數   //10位正整數 //0 到 4,294,967,295 //1張1000股
    unsigned long long Free_Stocks_Float;//自由流通股份 //10位正整數 //0 到 4,294,967,295 //1張1000股
    //如果是unsigned long long 是 0 到 18,446,744,073,709,551,615
    long long int The_Share_Volume_Of_Stocks;//股票成交量 //未做
    string Stock_Name;            //股票名稱     //可以限字數
    string Stock_Code;             //股票代碼     //可以限字數
    double Stock_Issue_Price;       //股票發行價
    double Stock_Listed_Price;      //股票上市價
    double Market_Value;            //股票市值         //未做
    double openingPrice;            //開盤價       //未做
    double closingPrice;            //收盤價       //未做
    double currentPrice;            //買賣價       //未做
    bool Close_Selling;             //是否暫停交易證券（1為是，0為否）//原本可以融券的股票，暫時不能再以融券賣出。//Short_Selling_Suspended
    int color;                      //紅色1(跌), 綠色2(漲), 白色0(維持)
public:
    Stock(string name = "", string code = "", unsigned long long volume = 0,unsigned long long freefloat = 0, double issuePrice = 0, double listedPrice = 0, double value = 0, double openPrice = 0, double closePrice = 0, double currentPrice = 0, bool close = 0)
    {
        //Num_Of_Stock = 0;//現有股票種類數量，計數用
        Stock_Name = name;
        Stock_Code = code;
        Stock_Volume = volume;
        Free_Stocks_Float = Stock_Volume;//初始自由流通股份
        Stock_Issue_Price = issuePrice;
        Stock_Listed_Price = listedPrice;
        Market_Value = value;
        openingPrice = openPrice;
        closingPrice = closePrice;
        currentPrice = currentPrice;
        Close_Selling = close;
        color = 0;
    }
    void Close_Selling_Stock(vector <Stock>); //暫停股票交易
    void Start_Selling_Stock(vector <Stock>); //恢復股票交易
    void Modify_Stock(vector <Stock>);//修改股票資料(管理員)
    void Delete_Stock();        //刪除股票(管理員)
    void Add_New_Stock();       //加入新股票(管理員)

    void Display_Stock_Market_Information();//顯示信息
    friend void Switch_choice(vector <Stock>, char);       //功能選擇
    void Market_Analysis();     //市場分析
    friend void Save(vector <Stock>);         //保存修改
//-----------------------------------------------------------------到111未用
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
    void setEverything(char*, char*, int, double, double, double, long long, long long, long long, long long, long long);
    friend void Write_File();//寫檔
    //以下為拿private data
    string getStock_Name()
    {
        return this -> Stock_Name;
    }
    string getStock_Code();
    double getStock_Issue_Price();
    double getStock_Listed_Price();
    double getMarket_Value();
    long long int getFree_Stocks_Float();
    long long int getThe_Share_Volume_Of_Stocks();
    double getOpeningPrice();
    double getClosingPrice();
    double getPrice();

    bool checkFloat();//檢查浮動 如果漲則true
    void randomChange(vector <Stock>);//隨時間改變目前的價格
};

/*void Stock::setEverything(char* name, char* code, int update, double issue, double listed, double market, long long floatStock, long long shareVolume, long long opening, long long closing, long long current)
{
    //設定class的private data
    strcpy(this->Stock_Name,name);
    //this->Stock_Name = name;
    strcpy(this->Stock_Code,code);
    //this->Stock_Code = code;
    this->updateTimes = update;
    this->Stock_Issue_Price = issue;
    this->Stock_Listed_Price = listed;
    this->Market_Value = market;
    this->Free_Stocks_Float = floatStock;
    this->The_Share_Volume_Of_Stocks = shareVolume;
    this->openingPrice = opening;
    this->closingPrice = closing;
    this->currentPrice = current;
}*/
//--------------------------------------------------------------------到這喔

void Interface(vector <Stock>);//介面選單

class Customer
{
    friend class Stock;
private:
    unsigned long int share_holding_value[10];//持有股票數量
    string Customer_Name;//用戶名
    string Customer_Password;//密碼
    string share_holding_name[10];//持有股票名稱
    string share_holding_code[10];//持有股票代碼

    double Balance;//現金餘額
    double Holding_Market_Value;//持有股票市值
    double Total_Assets;//總資產
    bool Administrator;//是否管理員
public:
    Customer()
    {
        Customer_Name = "";
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share_holding_name[i] = "";
            share_holding_code[i] = "";
            share_holding_value[i] = 0;
            Balance = Holding_Market_Value = Total_Assets = 0;
        }
    }
    void Log_In(string, vector <Stock>) const;//登錄
    void Register(Customer *);//註冊
    void Stock_Portfolio(vector <Stock>) const; // Portfolio--有價證券
    friend void Switch_choice(vector <Stock>, char);
    //----------------------------------------------------------------------------------到151未做
    /*
    void buy();//買
    void sell();//賣
    string getName();
    string getPass();
    holdingStock getHoldingStock();
    double getBalance();
    double getTotalAsset();
    bool getAdmin();
    */
    //-----------------------------------------------------------------------------------到這裡喔
};
Stock temp;//全局變量，聲明股票對象
Customer cust;//聲明用戶對象，全局變量


void Customer::Log_In(string pass_word, vector <Stock> share) const//登錄
{
    if( pass_word == Customer_Password )//核對密碼
    {
        Stock_Portfolio(share);
    }
    else
    {
        cout << endl;
        cout << "密碼錯誤"<<endl;
    }
}

void Customer::Register(Customer *cust)//註冊帳號
{
    char input;
    system("cls"); //執行系統命令：清屏=cls
    cin.get();
    cout << "歡迎進入---------------股票系統---------------" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "請輸入帳號/用戶名: ";
    cin >> Customer_Name;
    cout << "請輸入密碼(少於8字): " << endl;
    cin >> Customer_Password;
    while (Customer_Password.size() <= 0 || Customer_Password.size() > 8)
    {
        cout << "輸入錯誤" << endl;
        cout << "請輸入密碼(少於8字): " << endl;
        cin >> Customer_Password;
    }

    cout << endl;
    cout << "輸入您的初始資金:";
    cin >> Total_Assets;
    Holding_Market_Value = 0;
    Balance = Total_Assets;
    cout << "是否設為管理員?(y/n)" << endl;//大小寫都行
    cin >> input;
    if( (input == 'y') || (input == 'Y') )
    {
        Administrator = 1;
        cout << "已設定";
    }
    else if( (input == 'n') || (input == 'N') )
    {
        Administrator = 0;
    }
    else
    {
        cout << "默認為非管理員";
    }
    getch();
    system("cls");//清空
    cout << "已經完成註冊"     << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "按任意鍵返回" << endl;
    getch();
}

void Customer::Stock_Portfolio(vector <Stock> share) const//用戶交易操作介面系統
{
    int i,a;
    char input;
    string code;
    long int volume;
start:
    system("cls");
    cout << endl << endl;
    cout << "\t\t歡迎使用---------------股票系統---------------" << endl;
    cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t 用戶: " << cust.Customer_Name << endl << endl;
    cout << "\t\t 買入..........................[1]" << endl;
    cout << "\t\t 賣出..........................[2]" << endl;
    cout << "\t\t 恢復股票交易..................[3]" << endl;
    cout << "\t\t 暫停股票交易..................[4]" << endl;
    cout << "\t\t 修改股票代碼及名稱............[5]" << endl;//可以再新增要修改的
    cout << "\t\t 查看股市資訊..................[6]" << endl;
    cout << "\t\t 退出帳號......................[0]" << endl;
    cout << endl << "\t\t 輸入功能選項: ";

    cin >> input;

    if( (input>'6') || (input<'0') )
        goto start;
    else
    {
        switch(input)
        {
        case '0'://返回主頁面
        {
            Interface(share);
        }
        case '1': //買入
        {
            system("cls");
            cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                share[i].Display_Stock_Market_Information();//顯示市場信息
            }
            cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 持有股票市值\t可用資金\t總資產" << endl;
            cout << cust.Holding_Market_Value
                 << "\t\t" << cust.Balance
                 << "\t\t" << cust.Total_Assets << endl;
            cin.get();
            cout << endl << "輸入您要購買的股票代碼:";
            cin >> code;

            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "股票代碼應不大於5碼或至少有1碼" << endl;
                cout << "輸入您要購買的股票代碼:";
                cin >> code;
            }

            if( code != "" )//當輸入回車時報錯
            {
                int i = 0;
                flag = 0;
                while( (i < TOTALSTOCKS) && (!flag) )
                {
                    if ( code == share[i].Stock_Code)
                    {
                        if( share[i].Close_Selling == 1 )
                        {
                            cout << "股票已暫停交易!" << endl;
                            break;
                        }
                        else
                        {
                            int Max_Buy_Stock_Volume;//現金餘額可買股數
                            Max_Buy_Stock_Volume = int(cust.Balance/share[i].Stock_Listed_Price);//取整
                            cout << "您最多可購買量:" << Max_Buy_Stock_Volume << endl;
                            flag = 1;
                            cout << "輸入需要購買量: ";
                            cin >> volume;
                            while(volume != (int)volume)//判斷輸入是否為整數
                            {
                                cout<<"輸入錯誤,請重新輸入(整數)"<<endl;
                                cin >> volume;
                            }
                            if( (share[i].Free_Stocks_Float >= volume) && (cust.Balance >= volume*share[i].Stock_Listed_Price) )
                            {
                                //改動各數據
                                cust.share_holding_value[i] += volume;
                                cust.share_holding_name[i] = share[i].Stock_Name;
                                cust.share_holding_code[i] = share[i].Stock_Code;

                                share[i].Free_Stocks_Float -= volume;
                                cust.Balance -= share[i].Stock_Listed_Price*volume;
                                cust.Holding_Market_Value += share[i].Stock_Listed_Price*volume;
                                system("cls");
                                cout << "交易完成" << endl;
                                cout << endl;
                                cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
                                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                                cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
                                for(i=0; i < TOTALSTOCKS; i++)
                                {
                                    cout << " " << share[i].Stock_Name
                                         << "\t" << share[i].Stock_Code
                                         << "\t" << share[i].Stock_Volume
                                         << "\t" << cust.share_holding_value[i]
                                         << "\t" << share[i].Stock_Issue_Price
                                         << "\t " << share[i].Stock_Listed_Price
                                         << " \t " << (share[i].Close_Selling == 0 ?"未停券":"已停券") << endl;
                                }
                                cout << "持有股票市值\t可用資金\t目前總資產"  << endl;
                                cout << cust.Holding_Market_Value
                                     << "\t\t" << cust.Balance
                                     << "\t\t" << cust.Total_Assets << endl;
                                cin.get();
                                ofstream dataFile (cust.Customer_Name,ios::binary);
                                dataFile.write((char*)(&cust),sizeof(cust));
                                Save(share);
                            }
                            else if(share[i].Free_Stocks_Float <= volume)
                            {
                                cout << share[i].Stock_Name << "的可購股票數量少於您所需要股票數量";
                                cout << endl;
                                cout << "按任意鍵返回" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                            else if(cust.Balance <= volume*share[i].Stock_Listed_Price)
                            {
                                cout << "可用資金不足!";
                                cout << "按任意鍵返回" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                        }
                    }
                    else
                    {
                        i++;
                        while(i == TOTALSTOCKS)
                        {
                            system("cls");
                            cout << "輸入代碼錯誤" << endl;
                            cout << "按任意鍵返回" << endl;
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << "輸入格式錯誤" << endl;
                cout << "按任意鍵返回" << endl;
            }
            cin.get();
            break;
        }
        case '2':
        {
            //賣出股票
            system("cls");
            cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
            for(i=0; i < TOTALSTOCKS; i++)
            {
                cout << " " << share[i].Stock_Name
                     << "\t" << share[i].Stock_Code
                     << "\t" << share[i].Stock_Volume
                     << "\t" << cust.share_holding_value[i]
                     << "\t" << share[i].Stock_Issue_Price
                     << "\t " << share[i].Stock_Listed_Price
                     << " \t " << (share[i].Close_Selling == 0 ?"未停券":"已停券") << endl;
            }
            cout << "\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 持有股票市值\t可用資金\t目前總資產" << endl;
            cout << cust.Holding_Market_Value << "\t\t" << cust.Balance << "\t\t" << cust. Total_Assets << endl;
            cin.get();
            cout << endl << "輸入賣初股票代碼: ";
            code = "";
            while (code.size() > 6 || code.size() <= 0)
            {
                cout << "股票代碼應不大於6碼或至少有1碼" << endl;
                cout << "輸入您要購買的股票代碼:";
                cin >> code;
            }

            if(code != "")
            {
                i = 0;
                flag = 0;
                while( (i<TOTALSTOCKS) && (!flag) )
                {
                    if( share[i].Stock_Code == code )
                    {
                        if( share[i].Close_Selling == 1 )
                        {
                            cout << "股票已暫停交易!" << endl;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            cout << "輸入賣出量: ";
                            cin >> volume;
                            while(volume != (int)volume)//判斷輸入是否為整數
                            {
                                cout<<"輸入錯誤,請重新輸入(整數)"<<endl;
                                cin >> volume;
                            }
                            if(cust.share_holding_value[i] >= volume)
                            {
                                cust.share_holding_value[i] -= volume;
                                share[i].Free_Stocks_Float += volume;
                                cust.Balance += share[ i].Stock_Listed_Price*volume;
                                cust.Holding_Market_Value -= share[i].Stock_Listed_Price*volume;
                                system("cls");
                                cout << "交易成功!" << endl;
                                cout << endl;
                                ofstream data(cust.Customer_Name,ios::binary);
                                data.write((char*)(&cust),sizeof(cust));
                                Save(share);
                            }
                            else
                            {
                                cout << "您沒有足夠股票可賣出";
                                cout << "或您沒有購買此股票" << endl;
                                cout << "按任意鍵返回" << endl;
                                getch();
                                break;
                            }
                            cin.get();
                        }
                    }
                    else
                    {
                        i++;
                        while(i == TOTALSTOCKS)
                        {
                            system("cls");
                            cout << "您沒有購買該股票或您輸入錯誤" << endl;
                            cout << "按任意鍵返回";
                            getch();
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << endl << "輸入錯誤!";
            }
            cin.get();
            break;
        }
        case '3'://恢復股票交易
        {
            if(cust.Administrator == 1)
            {
                system("cls");
                cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//顯示市場信息
                }
                cin.get();
                temp.Start_Selling_Stock(share);
                break;
            }
            else
            {
                cout << "您無權恢復股票!" << endl;
                getch();
                break;
            }
        }
        case '4'://停券股票
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//顯示市場信息
                }
                cin.get();
                temp.Close_Selling_Stock(share);//進行
                break;
            }
            else
            {
                cout << "您無權掛起股票!" << endl ;
                getch();
                break;
            }
        }
        case '5'://修改股票
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//顯示市場信息
                }
                cin.get();
                temp.Modify_Stock(share);
                break;
            }
            else
            {
                cout << "您無權限停券股票!" << endl;
                getch();
                break ;
            }
        }
        case '6'://查看信息
            system("cls");
            cout << "\t\t\t******************************股票系統******************************" << endl;
            cout << "\t\t\t--------------------------------------------------------------------" << endl;
            cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
            for(int i=0; i<TOTALSTOCKS; i++)
            {
                cout << " "   << share[i].Stock_Name
                     << "\t\t" << share[i].Stock_Code
                     << "\t\t" << share[i].Stock_Volume
                     << "\t\t" << cust.share_holding_value[i]
                     << "\t\t" << share[i].Stock_Issue_Price
                     << "\t\t" << share[i].Stock_Listed_Price
                     << "\t\t" << (share[i].Close_Selling == 0?"未停券":"已停券") << endl;

            }
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 持有股票市值\t\t可用資金\t總資產"<<endl;
            cout << " " << cust.Holding_Market_Value
                 << "\t\t\t" << cust.Balance
                 << "\t\t" << cust.Total_Assets << endl;
            getch();
            break;
        }
        goto start;
    }
}

void Interface(vector <Stock> share)
{
    char choice;
    system("cls");
    cout << "***************股票交易系統***************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "進入股票交易市場................[1]" << endl;
    cout << "登陸用戶........................[2]" << endl;
    cout << "註冊新用戶......................[3]" << endl;
    cout << "退出本系統......................[0]" << endl;
    cout << endl << endl;
    cout << endl << "請選擇:";
    cin >> choice;
    switch (choice)
    {
    case '1':
    case '2':
    case '3':
    case '0':
        Switch_choice(share, choice);
    default:
        system("cls");
        Interface(share);
    }
}

void Switch_choice(vector <Stock> share, char choice)
{
    char pass_word[10];
    switch(choice)
    {
    case '0': //就退出
    {
        system("cls");
        cout << "感謝使用***************股票交易系統***************" << endl;
        cout << "\t不要再見!!!!!!!!!!!!!!!" << endl;
        exit(0);
    }
    case '1': //進入股票交易市場
    {
        system("cls");
        cout << "\n\n\t\t***************股票交易市場**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        //cout << " 公司\t\t代碼\t流通股\t可動股\t發行價\t上市價\t狀態" << endl;
        cout << " 公司名稱\t代碼\t\t流通股\t\t可動股\t\t\t發行價\t\t上市價\t\t狀態" << endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share[i].Display_Stock_Market_Information();//顯示市場信息
        }
        cin.get();
        getch();
        Interface(share);
        break;
    }
    case '2'://登陸用戶
    {
        system("cls");
        cout << "\n\n\t\t***************股票交易市場**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        cout << "輸入帳號:";
        cin >> cust.Customer_Name;
        cin.get();
        ifstream read_customer(cust.Customer_Name);//讀已有數據//要再修改
        while( !read_customer.eof() )//判斷是否有記錄
        {
            read_customer.read((char*)(&cust),sizeof(cust));
            if( read_customer.fail() )
            {
                cout << endl;
                cout << "資料庫沒有記錄" << endl;
                getch();
                Interface(share);
            }
            else
            {
                cout << "用戶密碼:";
                char input;
                int i=0;
                cout << "輸入密碼:"<<endl;
                cout.flush();
                input = getch();
                while(input != 13)
                {
                    pass_word[i++] = input;
                    cout << '*';
                    cout.flush();
                    input = getch();
                }
                pass_word[i] = 0;
                if( strcmp(pass_word,"") != 0 )
                {
                    cust.Log_In(pass_word, share);
                    cin.get();
                    Interface(share);
                    break;
                }
                else
                {
                    cout << endl << "輸入錯誤!";
                }
                read_customer.close();
                cin.get();
                break;
            }
        }
    }
    case '3':  //註冊新用戶
    {
        system("cls");
        cout << "註冊新用戶" << endl;
        cout << "~~~~~~~~~~" << endl;
        cust.Register(&cust);
        ofstream write_customer(cust.Customer_Name);
        write_customer.write((char*)&cust,sizeof(cust));
        write_customer.close();
        Interface(share);
        break;
    }
    default:
        break;
    }
}

/*void Stock::Add_New_Stock()//添加新股票
{
    string name = "", code = "";
    system("cls");
    cin.get();
    cout << "輸入新股票名(字數要限制): ";
    cin >> name;

    while (name.size() > 20 || name.size() <= 0)
    {
        cout << "股票名稱應不大於20碼或至少有1碼" << endl;
        cout << "輸入您要購買的股票名稱:";
        cin >> name;
    }
    cout << "輸入股票代碼(五個以內): ";
    cin >> code;
    while (code.size() > 5 || code.size() <= 0)
    {
        cout << "股票代碼應不大於5碼或至少有1碼" << endl;
        cout << "輸入您要購買的股票代碼:";
        cin >> code;
    }
    cout << "輸入流通股票數量: ";
    cin >> Stock_Volume;
    cout << "輸入股票發行價: ";
    cin >> Stock_Issue_Price;
    cin.get();
    Free_Stocks_Float = Stock_Volume;
    Num_Of_Stock++;
    srand(time(NULL));//隨機生成股票上市價
    Stock_Listed_Price = (rand()%3+1)*Stock_Issue_Price + rand()%1000/10;//亂數調整
}*/

void Stock::Display_Stock_Market_Information()
{
    cout << " "   << Stock_Name
         << "\t\t" << Stock_Code
         << "\t\t" << Stock_Volume
         << "\t\t" << cust.share_holding_value
         << "\t\t" << Stock_Issue_Price
         << "\t\t" << Stock_Listed_Price
         << "\t\t" << (Close_Selling == 0?"未停券":"已停券") << endl;
}

/*void readFile()
{
    int update;//更新次數
    double issuePrice, listedPrice, marketValue, opening, closing, current;//發行價 上市價 市值 開盤 收盤 買賣價
    string name, code;//名子 代碼
    long long floatNumber, shareVolume;// 股票成交量 自由流通股份
    ifstream stockData;
    for (int i=0; i<TOTALSTOCKS; i++)
    {
        stockData.open("stockData" + enterprise[i] + ".txt");
        if (!stockData)
        {
            cout <<"Unable to open: "<< "stockData" << enterprise[i] << endl;
        }
        else {
            while (stockData >> name)//反覆讀入直到讀到最後(最新)的一行資料
            {
                stockData >> code >> update >> issuePrice >> listedPrice >> marketValue
                >> floatNumber >> shareVolume >> opening >> closing >> current;
            }
            char Name[20], Code[6];
            strcpy(Name,name.c_str());
            strcpy(Code,code.c_str());
            share[i].setEverything(Name, Code, update, issuePrice, listedPrice, marketValue, floatNumber, shareVolume, opening, closing, current);
        }
        stockData.close();
    }
}*/
/*
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
*/
void Stock::Close_Selling_Stock(vector <Stock> share)//暫停股票交易
{
    char input;
    string share_code = "";
    cout<<"輸入您要停券的股票代碼:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "股票代碼應不大於5碼或至少有1碼" << endl;
        cout << "輸入您要購買的股票代碼:";
        cin >> share_code;
    }
    int i=0;
    flag = 0;
    if( share_code != "")//當輸入回車時報錯
    {
        while( (i<TOTALSTOCKS) && (!flag) )
        {
            if(share[i].Stock_Code == share_code)
            {
                flag = 1;
                cout << "確定(y/n)";
                cin >> input;
                if(input == 'y')
                {
                    share[i].Close_Selling = 1;
                    Save(share);
                    cout << "已停券" << endl;
                    cout << endl;
                    break;
                }
                else if(input=='n')
                {
                    cout << "步奏取消!" << endl;
                }
                else
                {
                    cout << "輸入錯誤!" <<endl;
                }
            }
            else i++;
            if(i == TOTALSTOCKS)
            {
                cout << "您輸入的代碼錯誤!" << endl;
                break;
            }
        }
    }
    getch();
}

void Stock::Start_Selling_Stock(vector <Stock> share)//恢復股票交易
{
    char input;
    string share_code = "";
    cout << "輸入您要恢復交易的股票代碼:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "股票代碼應不大於5碼或至少有1碼" << endl;
        cout << "輸入您要恢復交易的股票代碼:";
        cin >> share_code;
    }
    int i= 0;
    flag = 0;
    while( (!flag) && (i<TOTALSTOCKS) )
    {
        if( share[i].Stock_Code == share_code )
        {
            flag = 1;
            cout << "確定(y/n)";
            cin >> input;
            if(input == 'y')
            {
                share[i].Close_Selling = 0;
                Save(share);
                cout << "已恢復" << endl;
                cout << endl;
                break;
            }
            else if(input == 'n')
            {
                cout << "步驟取消!" << endl;
            }
            else
            {
                cout << "輸入錯誤!" <<endl;
            }
        }
        else i++;
        if(i == TOTALSTOCKS)
        {
            cout << "您輸入的代碼錯誤!" << endl;
            break;
        }
    }
    getch();
}

/*void Stock::Delete_Stock()//刪除股票
{
    char input,share_code[6];
    cout << "輸入刪除股票代碼:";
    cin.getline(share_code,6);
    int i= 0;
    flag = 0;
    if( strcmp(share_code,"") != 0 )//當輸入回車時報錯
    {
        while( (i<TOTALSTOCKS) && (!flag) )
        {
            if( strcmp(share[i].Stock_Code,share_code) == 0 )
            {
                flag = 1;
                cout << "確定(y/n)";
                cin >> input;
                if(input == 'y')
                {
                    cust.Balance += share[i].Stock_Listed_Price*cust.share_holding_value[i];
                    cust.Holding_Market_Value -= share[i].Stock_Listed_Price *cust.share_holding_value[i];
                    cust.share_holding_value[i] = 0;
                    strcpy(share[i].Stock_Name,"");
                    strcpy(share[i].Stock_Code,"");
                    strcpy(cust.share_holding_name[i ],"");
                    strcpy(cust.share_holding_code[i],"");
                    Num_Of_Stock--;
                    share[i].Stock_Volume = 0;
                    share[i].Free_Stocks_Float = 0;
                    share[i].Stock_Listed_Price = 0;
                    share[i].Stock_Issue_Price = 0;
                    temp.Save(share);
                    ofstream data(cust.Customer_Name,ios::binary);
                    data.write((char*)(&cust),sizeof(cust));
                    break;
                }
                else if(input=='n')
                {
                    cout << "步驟取消!" << endl;
                }
                else
                {
                    cout << "輸入錯誤!" << endl;
                }
            }
            else i++;
            while(i == TOTALSTOCKS)
            {
                cout << "您輸入的代碼錯誤!" << endl;
                break;
            }
        }
    }
    else
    {
        cout<<"輸入錯誤!";
    }
}*/

void Stock::Modify_Stock(vector <Stock> t)//調整資訊
{
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "輸入原公司代碼" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "股票代碼應不大於5碼或至少有1碼" << endl;
        cout << "輸入您要恢復交易的股票代碼:";
        cin >> share_code;
    }
    if( share_code != "" )//當輸入回車鍵時報錯
    {
        while( (i < TOTALSTOCKS) && (!flag) )
        {
            if (t[i].Stock_Code == share_code)
            {
                if(t[i].Close_Selling == 1)
                {
                    cout<<"暫停股票交易!"<<endl;
                    break;
                }
                else
                {
                    cin.clear();
                    flag = 1;
                    cout << "輸入新股名(忘了多少以內):" << endl;
                    cin >> share_name;
                    while (share_name.size() > 20 || share_name.size() <= 0)
                    {
                        cout << "股票名稱應不大於20碼或至少有1碼" << endl;
                        cout << "輸入您要購買的股票名稱:";
                        cin >> share_name;
                    }
                    t[i].Stock_Name = share_name;
                    cin.get();
                    cout << "輸入新代碼(5以內)";
                    cout << endl;
                    cin >> share_code;
                    while (share_code.size() > 5 || share_code.size() <= 0)
                    {
                        cout << "股票代碼應不大於5碼或至少有1碼" << endl;
                        cout << "輸入您要恢復交易的股票代碼:";
                        cin >> share_code;
                    }
                    t[i].Stock_Code = share_code;
                    Save(t);
                }
            }
            else
            {
                i++;
            }
            if(i==TOTALSTOCKS)
            {
                cout << "股票不存在!" << endl;
                cout << "按任意鍵返回..." << endl;
                getch();
            }
        }
    }
    else
    {
        cout << "輸入錯誤!";
    }
}

void Save(vector <Stock> t)
{
    ofstream write_data("Stock_File.txt");
    for(int i=0; i < TOTALSTOCKS; i++)
    {
        write_data.write((char*)(&t[i]),sizeof(t[i]));
    }
}

void Stock::randomChange(vector <Stock> share)
{
    int i = 0;
    int lastTime = 0;
    while (1) {
        int now = getTime();
        /*------ 每過30秒浮動--------*/
        if (now - lastTime > 30) {
            for(int j=0; j<share.size(); j++) {
                double amount_of_increase = Random(); //浮動百分比

                if(amount_of_increase == 0) {        //維持不動
                    share[i].color = 0;
                }
                else if(amount_of_increase > 0) {       //上漲

                    share[i].Stock_Listed_Price *= (1 + amount_of_increase);

                    if(amount_of_increase == 0.1) {     //漲幅達10%
                        share[i].color = 2;
                        share[i].Close_Selling = 1;
                    }
                    else {                              //漲幅小於10%
                       share[i].color = 2;
                       share[i].Stock_Listed_Price *= (1 + amount_of_increase);
                    }
                }
                else if(amount_of_increase < 0) {        //下跌

                    share[i].Stock_Listed_Price *= (1 + amount_of_increase);

                    if(amount_of_increase == -0.1) {    //下跌達10%
                        share[i].color = 1;
                        share[i].Close_Selling = 1;
                    }
                    else {                               //下跌小於10%
                        share[i].color = 1;
                    }
                }
            }
            lastTime = now;
        }
    }
}

int getTime()
{
    return clock()/CLOCKS_PER_SEC;
}

double Random()
{
    srand(time(nullptr));
    int Min = -10;
    int Max = 10;
    int x = rand() % (Max - Min + 1) + Min; // x的範圍[-10, 10]
    return x*0.01; //換百分比
}

int main()
{
    ifstream dataFile("Stock_File.txt"); //讀取股票數據
    vector <Stock> share;

    if (!dataFile)
    {
        cout << "Can not open Stock_file.txt" << endl;
    }
    else {
        unsigned long long volume, freefloat;
        string name, code;
        double value, openPrice, closePrice, currentPrice, issuePrice, listedPrice;
        bool close;
        int i=0;
        while (dataFile >> name >> code >> volume >> freefloat >> issuePrice >> listedPrice >> value >> openPrice >> closePrice >> currentPrice >> close)
        {
            Stock tmp(name, code, volume, freefloat, issuePrice, listedPrice, value, openPrice, closePrice, currentPrice, close);
            share.push_back(tmp);
        }
    }
    thread t1(&Stock::randomChange, &temp, share);  //多執行序，執行股票浮動
    t1.detach();
    Interface(share);
}
