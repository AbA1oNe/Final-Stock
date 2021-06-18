#include <iostream>
#include <cstring>
#include <conio.h>//getch()
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#include <cstdlib>
using namespace std;

const int TOTALSTOCKS = 10;//設定有放幾個股票的資料
int flag;
double Random();    //浮動股票的Function
int main();

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Stock_Volume;    //股票總股數   //10位正整數 //0 到 4,294,967,295 //1張1000股
    unsigned long long Free_Stocks_Float;//自由流通股份 //10位正整數 //0 到 4,294,967,295 //1張1000股
    long long int The_Share_Volume_Of_Stocks;//???????q //????
    string Stock_Name;            //股票名稱
    string Stock_Code;             //股票代碼
    double Stock_Issue_Price;       //股票發行價
    double Stock_Listed_Price;      //股票上市價
    double Market_Value;            //股票市值
    double openingPrice;            //開盤價 
    double closingPrice;            //收盤價       //未做
    double currentPrice;            //買賣價
    bool Close_Selling;             //是否暫停交易證券（1為是，0為否）//原本可以融券的股票，暫時不能再以融券賣出。//Short_Selling_Suspended
    int color;                      //顏色
public:
    Stock(string name = "", string code = "", unsigned long long volume = 0,unsigned long long freefloat = 0, double issuePrice = 0, double listedPrice = 0, double value = 0, double openPrice = 0, double closePrice = 0, double currentPrice = 0, bool close = 0)
    {
        //Num_Of_Stock = 0;//?{???????????q?A?p???
        Stock_Name = name;
        Stock_Code = code;
        Stock_Volume = volume;
        Free_Stocks_Float = Stock_Volume;//??l???y?q???
        Stock_Issue_Price = issuePrice;
        Stock_Listed_Price = listedPrice;
        Market_Value = value;
        openingPrice = openPrice;
        closingPrice = closePrice;
        currentPrice = currentPrice;
        Close_Selling = close;
        color = 0;
    }
    void Close_Selling_Stock(vector <Stock>); //?????????
    void Start_Selling_Stock(vector <Stock>); //??_??????
    void Modify_Stock(vector <Stock>);//????????(??z??)
    void Delete_Stock();        //?R?????(??z??)
    void Add_New_Stock();       //?[?J?s???(??z??)

    void Display_Stock_Market_Information();//???H??
    friend void Switch_choice(vector <Stock>, char, time_t);       //?\????
    void Market_Analysis();     //???????R
    friend void Save(vector <Stock>);         //?O?s???
//-----------------------------------------------------------------??111????
    /*?i??U??????H??
    (
    1.?}?L???GOpening Price
    2.???L???GClosing Price
    3.?????GLimit Up
    4.?^???GLimit Down
    5.???? : Price
    ......??
    )
    */
    void setEverything(char*, char*, int, double, double, double, long long, long long, long long, long long, long long);
    friend void Write_File();//?g??
    //?H?U????private data
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

    bool checkFloat();//??d?B?? ?p?G???htrue
    void randomChange(vector <Stock>);//?H????????e??????
};

/*void Stock::setEverything(char* name, char* code, int update, double issue, double listed, double market, long long floatStock, long long shareVolume, long long opening, long long closing, long long current)
{
    //?]?wclass??private data
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
//--------------------------------------------------------------------??o??

void Interface(vector <Stock>, time_t);//???????

class Customer
{
    friend class Stock;
private:
    unsigned long int share_holding_value[10];//?????????q
    string Customer_Name;//?Τ?W
    string Customer_Password;//?K?X
    string share_holding_name[10];//????????W??
    string share_holding_code[10];//????????N?X

    double Balance;//?{???l?B
    double Holding_Market_Value;//???????????
    double Total_Assets;//?`??
    bool Administrator;//?O?_??z??
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
    void Log_In(string, vector <Stock>, time_t) const;//?n??
    void Register(Customer *);//???U
    void Stock_Portfolio(vector <Stock>, time_t) const; // Portfolio--???????
    friend void Switch_choice(vector <Stock>, char, time_t);
    //----------------------------------------------------------------------------------??151????
    /*
    void buy();//?R
    void sell();//??
    string getName();
    string getPass();
    holdingStock getHoldingStock();
    double getBalance();
    double getTotalAsset();
    bool getAdmin();
    */
    //-----------------------------------------------------------------------------------??o???
};
Stock temp;//??????q?A?n???????H
Customer cust;//?n???Τ??H?A??????q


void Customer::Log_In(string pass_word, vector <Stock> share, time_t startTime) const//?n??
{
    if( pass_word == Customer_Password )//???K?X
    {
        Stock_Portfolio(share, startTime);
    }
    else
    {
        cout << endl;
        cout << "密碼錯誤"<<endl;
    }
}

void Customer::Register(Customer *cust)//???U?b??
{
    char input;
    system("cls"); //????t?ΩR?O?G?M??=cls
    cin.get();
    cout << "歡迎進入---------------股票系統---------------" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "請輸入帳號/用戶名: ";
    cin >> Customer_Name;
    cout << "請輸入密碼(少於8 字): " << endl;
    cin >> Customer_Password;
    while (Customer_Password.size() <= 0 || Customer_Password.size() > 8)
    {
        cout << "密碼不能大於8個字元及至少要有一個字元" << endl;
        cout << "請輸入密碼(少於8 字): " << endl;
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

void Customer::Stock_Portfolio(vector <Stock> share, time_t startTime) const//?Τ?????@?????t??
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
    cout << "\t\t 修改股票代碼及名稱............[5]" << endl;//?i?H?A?s?W?n???
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
        case '0'://??^?D????
        {
            main();
        }
        case '1': //?R?J
        {
            time_t endtime = time(NULL);
            for (int j=0; j<(endtime - startTime) / 10; j++)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; // x???d??[-10, 10]
                    double result = x * 0.01;
                    
                    double original = share[i].Stock_Listed_Price;
                    share[i].Stock_Listed_Price = (1+result) * share[i].Stock_Listed_Price;
                    if (original < share[i].Stock_Listed_Price)//漲
                    {
                        share[i].color = 12;
                    }
                    else if (original > share[i].Stock_Listed_Price)
                    {
                        share[i].color = 10;
                    }
                    Sleep(10);
                }
            }
            system("cls");
            cout << "\t\t\t------------------------------股票系統------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                share[i].Display_Stock_Market_Information();//???????H??
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
                cout << "股票代碼需小於5碼及至少有一碼" << endl;
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
                            Max_Buy_Stock_Volume = int(cust.Balance/share[i].Stock_Listed_Price);//????
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
            cout << endl << "輸入賣出股票代碼: ";
            code = "";
            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "股票代碼應小於5碼及至少有一碼" << endl;
                cout << "輸入賣出股票代碼: ";
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
                            while(volume != (int)volume)//?P?_??J?O?_?????
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
        case '4'://??????
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
                cout << "您無權限修改股票!" << endl;
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

void Interface(vector <Stock> share, time_t startTime)
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
        Switch_choice(share, choice, startTime);
    default:
        system("cls");
        main();
    }
}

void Switch_choice(vector <Stock> share, char choice, time_t startTime)
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
        time_t endtime = time(NULL);
        for (int j=0; j<(endtime - startTime) / 10; j++)
        {
            for (int i=0; i<TOTALSTOCKS; i++)
            {
                srand(time(NULL));
                double x = rand() % 21 -10; // x???d??[-10, 10]
                double result = x * 0.01;
                
                double original = share[i].Stock_Listed_Price;
                share[i].Stock_Listed_Price = (1+result) * share[i].Stock_Listed_Price;
                if (original < share[i].Stock_Listed_Price)//漲
                {
                    share[i].color = 12;
                }
                else if (original > share[i].Stock_Listed_Price)
                {
                    share[i].color = 10;
                }
                Sleep(10);
            }
        }

        system("cls");
        cout << "\n\n\t\t***************股票交易市場**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        cout << " 公司名稱\t\t代碼\t流通股\t\t可動股\t\t發行價\t\t上市價\t\t狀態" << endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share[i].Display_Stock_Market_Information();//顯示市場信息
        }
        cin.get();
        getch();
        main();
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
                main();
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
                    cust.Log_In(pass_word, share, startTime);
                    cin.get();
                    main;
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
        main();
        break;
    }
    default:
        break;
    }
}

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

void Stock::Close_Selling_Stock(vector <Stock> share)//暫停股票交易
{
    char input;
    string share_code = "";
    cout<<"輸入您要停券的股票代碼:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "股票代碼需小於5及至少有一碼" << endl;
        cout << "輸入您要停券的股票代碼:";
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
        cout << "股票代碼需小於5碼或至少大於一碼" << endl;
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

void Stock::Modify_Stock(vector <Stock> t)//調整資訊
{
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "輸入原公司代碼:" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "股票代碼需小於5碼及至少有一碼" << endl;
        cout << "輸入原公司代碼:";
        cin >> share_code;
    }
    if( share_code != "" )
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
                    cout << "輸入新股名(20字元以內):" << endl;
                    cin >> share_name;
                    while (share_name.size() > 20 || share_name.size() <= 0)
                    {
                        cout << "股票名稱需小於20字元及大於一字元" << endl;
                        cout << "輸入新股名(20字元以內):";
                        cin >> share_name;
                    }
                    t[i].Stock_Name = share_name;
                    cin.get();
                    cout << "輸入新股票代碼(5碼以內):";
                    cout << endl;
                    cin >> share_code;
                    while (share_code.size() > 5 || share_code.size() <= 0)
                    {
                        cout << "股票代碼需小於5碼及大於一碼" << endl;
                        cout << "輸入新股票代碼(5碼以內):";
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

int main()
{
    ifstream dataFile("Stock_File.txt");
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
    time_t startTime;
    startTime = time(NULL);
    Interface(share, startTime);
}
