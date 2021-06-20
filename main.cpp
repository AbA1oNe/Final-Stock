#include <iostream>
#include <conio.h>//getch()
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

const int TOTALSTOCKS = 10;//Total stocks number
time_t startTime;
double Random();// function that controls the float
int main();

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Free_Stocks_Float;//How many shares of stocks available on the market
    string Stock_Name;
    string Stock_Code;
    double Stock_Listed_Price;//The original price on the market
    double Market_Value;
    double currentPrice;
    bool Close_Selling;//Trading stopped or not
    int color;//1 for red, 2 for green, 3 for white, indicating increase or decrease
public:
    Stock(string name = "", string code = "",unsigned long long freefloat = 0, double listedPrice = 0, double value = 0, double current = 0, bool close = 0)
    {
        Stock_Name = name;
        Stock_Code = code;
        Free_Stocks_Float = freefloat;
        Stock_Listed_Price = listedPrice;
        Market_Value = value;
        currentPrice = current;
        Close_Selling = close;
        color = 3;
    }
    void Close_Selling_Stock(vector <Stock>&, vector <Customer>, int); //Stop trading
    void Start_Selling_Stock(vector <Stock>&, vector <Customer>, int); //Resume trading
    void Modify_Stock(vector <Stock>&);

    friend void Display_Stock_Market_Information(vector <Stock>, int, double[]);
    void Switch_choice(vector <Stock>, char,vector <Customer>); //Menu
    friend void StockWrite(vector <Stock>);
};

void Interface(vector <Stock>, vector <Customer>);

class Customer
{
    friend class Stock;
private:
    double share_holding_value[10] = {0};   //The shares of stock owned
    string Customer_Name;
    string Customer_Password;
    string share_holding_name[10] = {"$"};// Names of stocks owned, $ as no name for now
    string share_holding_code[10] = {"$"};// Codes of stocks owned

    double Balance;
    double Holding_Market_Value;
    double Total_Assets;
    bool Administrator;
public:
    Customer(string CusName = "", string CusPass = "", vector <string> VHoldName = {"$"},
             vector <string> VHoldCode = {"$"}, vector <double> VHoldValue = {0},
             double B = 0, double HMV = 0, double TA = 0, bool Admin = 0)
    {
        Customer_Name = CusName;
        Customer_Password = CusPass;
        for(int i=0; i<VHoldName.size(); i++)
        {
            share_holding_name[i] = VHoldName[i];
        }
        for(int i=0; i<VHoldCode.size(); i++)
        {
            share_holding_code[i] = VHoldCode[i];
        }
        for(int i=0; i<VHoldValue.size(); i++)
        {
            share_holding_value[i] = VHoldValue[i];
        }
        Balance = B;
        Holding_Market_Value = HMV;
        Total_Assets = TA;
        Administrator = Admin;
    }
    void Count_Total_Assets(vector <Stock>, vector <Customer>, int );
    void Log_In(string, vector <Stock>, time_t) const;
    void Register(vector <Customer>);
    friend void Display_Stock_Market_Information(vector <Stock>, int);
    void Stock_Portfolio(vector <Stock>, vector <Customer>, int ) const;// Stock market menu
    friend void CustomerWrite(vector <Customer>);
};

void Customer::Count_Total_Assets(vector <Stock> share, vector <Customer> cus, int index)
{
    cus[index].Total_Assets=0;
    for(int i=0; i<10; i++)
    {
        Total_Assets += share[i].currentPrice*cus[index].share_holding_value[i];
    }
    cus[index].Total_Assets += cus[index].Balance;
}

void Customer::Register(vector <Customer> cus)//Register
{
    string Name,Password;
    double TotalAssets, Balbace;
    char input;
    bool Admin;
    bool flag;
    ofstream WriteFile("Customer.txt",ios::app);
    if(!WriteFile)
    {
        cout<< "can't open the file" <<endl;
    }
    else
    {
        cout << "Please enter your username: ";
        while(cin>>Name)
        {
            flag = 0;
            for(int i=0; i<cus.size(); i++)
            {
                if(Name == cus[i].Customer_Name)
                {
                    flag = 1;
                    break;
                }
            }
            if(!flag)
            {
                break;
            }
            system("cls");
            cout<<"The username has been used" <<endl;
            cout<< "Please enter your username: ";
        }
        cout << endl << "Please enter your password:";
        cin >> Password;
        cout << endl << "Please enter your starting money: ";
        cin>> TotalAssets;
        Balbace = TotalAssets;
        cout << endl << "Administrator or not?(y/n)" << endl;
        cin>> input;
        if( (input == 'y') || (input == 'Y'))
        {
            Admin = 1;
            cout << "Set!";
        }
        else if( (input == 'n') || (input == 'N') )
        {
            Admin = 0;
            cout << "Set!";
        }
        else
        {
            cout << "Default as not a admin"<<endl;
        }
        WriteFile << endl << Name << ' ' << Password << ' ' ;
        for(int j=0; j<2; j++)
        {
            for(int i=0; i<10; i++)
            {
                if(i == 9)
                {
                    WriteFile << "$" << ' ' << "|" <<' ';// | indicates the end of the data
                }
                else
                {
                    WriteFile << "$" <<' ';
                }
            }
        }
        for(int i=0; i<10 ; i++)
        {
            WriteFile << "0" <<' ';
        }
        WriteFile << "|" <<' '<< Balbace << ' ' << 0 << ' ' << TotalAssets << ' ' << Admin;

        WriteFile.close();
        vector <string> nothing;
        vector <double> nothing1;
        Customer t(Name, Password, nothing, nothing, nothing1, Balbace, 0, TotalAssets, Admin);
        cus.push_back(t);
        getch();
        system("cls");
        cout << "Done!"     << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Hit any key to return" << endl;
        getch();
    }
}

void Customer::Stock_Portfolio(vector <Stock> share, vector <Customer> cus, int index) const//Stock market menu
{
    int flag;
    int i,a;
    char input;
    string code;
    long int volume;
start:
    system("cls");
    cout << endl << endl;
    cout << "\t\tWelcome to---------------The Stock System---------------" << endl;
    cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t User: " << cus[index].Customer_Name << endl << endl;
    cout << "\t\t Buy..........................[1]" << endl;
    cout << "\t\t Sell..........................[2]" << endl;
    cout << "\t\t Resume a stock's trading..................[3]" << endl;
    cout << "\t\t Pause a stock's trading..................[4]" << endl;
    cout << "\t\t Modify a stock's name or code............[5]" << endl;
    cout << "\t\t Check the stock market..................[6]" << endl;
    cout << "\t\t Exit......................[0]" << endl;
    cout << endl << "\t\t Enter an option: ";

    cin >> input;

    if( (input>'6') || (input<'0') )
        goto start;
    else
    {
        switch(input)
        {
        case '0'://exit
        {
            CustomerWrite(cus);
            StockWrite(share);
            main();
        }
        case '1': //buy
        {
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            system("cls");
            for(int i=0; i<100; i++)
            {
                cout<< " ";
            }
            cout<< "The Stock System" <<endl;
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                 << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                Display_Stock_Market_Information(share, i, floatRange);
            }
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << right << setw(20) << "Market Value of Holding Stock" << setw(10) << "Money" << setw(20) << "Total Assets"<< endl;
            cus[index].Count_Total_Assets(share, cus, index);
            cout << right << setw(15) << cus[index].Holding_Market_Value << setw(22) << cus[index].Balance
                 << setw(17) << cus[index].Total_Assets << endl;

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\t\t\t\tStock you own" << endl << endl;
            cout << right << setw(20) << "Name" << setw(20) << "Code" << setw(20) << "Shares" << endl;

            for (int j=0; j<TOTALSTOCKS; j++)
            {
                if (cus[index].share_holding_name[j] == "$")//this means no name in the array
                {
                    continue;
                }
                else
                {
                    cout << right << setw(20) << cus[index].share_holding_name[j] << setw(20)
                         << cus[index].share_holding_code[j] << setw(20) << cus[index].share_holding_value[j] << endl;
                }
            }
            cin.get();
            cout << endl << "Enter the stock code you want to buy: (Enter 0 to return)";
            cin >> code;
            if (code == "0")
            {
                goto start;
            }

            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "Stock code has to be less than 5 characters or 1 above" << endl;
                cout << "Enter the stock code you want to buy: (Enter 0 to return)";
                cin >> code;
                if (code == "0")
                {
                    goto start;
                }
            }

            if( code != "" )
            {
                int i = 0;
                flag = 0;
                while( (i < TOTALSTOCKS) && (!flag) )
                {
                    if ( code == share[i].Stock_Code)
                    {
                        if( share[i].Close_Selling == 1 )
                        {
                            cout << "The stock has paused the trade" << endl;
                            break;
                        }
                        else
                        {
                            int Max_Buy_Stock_Volume;//To calculate how many shares at most the user can but with its balance
                            Max_Buy_Stock_Volume = int(cus[index].Balance/share[i].currentPrice);
                            cout << "At most you can buy:" << Max_Buy_Stock_Volume << endl;
                            if (Max_Buy_Stock_Volume == 0)
                            {
                                cout << "Not enough money" << endl;
                                cout << "Hit any key to return" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                            flag = 1;
                            cout << "Enter how much you want to buy: ";
                            cin >> volume;
                            while(volume != (int)volume)//To check if volume is an integer
                            {
                                cout<<"Please enter an integer"<<endl;
                                cin >> volume;
                            }
                            if( (share[i].Free_Stocks_Float >= volume) && (cus[index].Balance >= volume*share[i].currentPrice) )
                            {
                                //Modifying datas
                                cus[index].share_holding_value[i] += volume;
                                cus[index].share_holding_name[i] = share[i].Stock_Name;
                                cus[index].share_holding_code[i] = share[i].Stock_Code;

                                share[i].Free_Stocks_Float -= volume;
                                cus[index].Balance -= share[i].currentPrice*volume;
                                cus[index].Holding_Market_Value += share[i].currentPrice*volume;
                                system("cls");
                                cout << "Done" << endl;
                                cout << endl;
                                cout << "Market Valuse of Holding Stock\tMoney\tTotal Assets"  << endl;
                                cus[index].Count_Total_Assets(share, cus, index);
                                cout << cus[index].Holding_Market_Value
                                     << "\t\t" << cus[index].Balance
                                     << "\t\t" << cus[index].Total_Assets << endl;
                                cin.get();

                                StockWrite(share);
                                goto start;
                            }
                            else if(share[i].Free_Stocks_Float <= volume)
                            {
                                cout << share[i].Stock_Name << "has less stocks than you want to buy";
                                cout << endl;
                                cout << "Hit any key to return" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                            else if(cus[index].Balance <= volume*share[i].currentPrice)
                            {
                                cout << "Not enough money" << endl;
                                cout << "Hit any key to return" << endl;
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
                        if(i == TOTALSTOCKS-1)
                        {
                            system("cls");
                            cout << "Wrong code" << endl;
                            cout << "Hit any ket to return" << endl;
                            getch();
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << "Wrong format" << endl;
                cout << "Hit any key to return" << endl;
                cin.get();
                goto start;
            }
            cin.get();
            break;
        }
        case '2':
        {
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            system("cls");
            for(int i=0; i<100; i++)
            {
                cout<< " ";
            }
            cout<< "The Stock System" <<endl;
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                 << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                Display_Stock_Market_Information(share, i, floatRange);
            }
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << right << setw(20) << "Market Value of Holding Stock" << setw(10) << "Money" << setw(20) << "Total Assets"<< endl;
            cus[index].Count_Total_Assets(share, cus, index);
            cout << right << setw(15) << cus[index].Holding_Market_Value << setw(22) << cus[index].Balance
                 << setw(17) << cus[index].Total_Assets << endl;


            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\t\t\t\tStock you own" << endl << endl;
            cout << right << setw(20) << "Name" << setw(20) << "Code" << setw(20) << "Shares" << endl;

            for (int j=0; j<TOTALSTOCKS; j++)
            {
                if (cus[index].share_holding_name[j] == "$")//this means no name in the array
                {
                    continue;
                }
                else
                {
                    cout << right << setw(20) << cus[index].share_holding_name[j] << setw(20)
                         << cus[index].share_holding_code[j] << setw(20) << cus[index].share_holding_value[j] << endl;
                }
            }
            cin.get();

            cout << endl << "Enter the stock code you want to sell: ";
            code = "";
            cin >> code;
            if (code == "0")
            {
                goto start;
            }

            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "Stock code has to be less than 5 characters or 1 above" << endl;
                cout << "Enter the stock code you want to sell: (Enter 0 to return)";
                cin >> code;
                if (code == "0")
                {
                    goto start;
                }
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
                            cout << "The stock has paused trading" << endl;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            cout << "Enter how much you want to sell: ";
                            cin >> volume;
                            while(volume != (int)volume)
                            {
                                cout<<"Please enter an integer"<<endl;
                                cin >> volume;
                            }
                            if(cus[index].share_holding_value[i] >= volume)
                            {
                                cus[index].share_holding_value[i] -= volume;
                                share[i].Free_Stocks_Float += volume;
                                cus[index].Balance += share[i].currentPrice*volume;
                                cus[index].Holding_Market_Value -= share[i].currentPrice*volume;
                                system("cls");
                                cout << "Done" << endl;
                                cout << endl;

                                StockWrite(share);
                            }
                            else
                            {
                                cout << "You don't have enough stocks to sell";
                                cout << endl;
                                cout << "Hit any key to return" << endl;
                                getch();
                                break;
                            }
                            cin.get();
                        }
                    }
                    else
                    {
                        i++;
                        if(i == TOTALSTOCKS-1)
                        {
                            system("cls");
                            cout << "Wrong code" << endl;
                            cout << "Hit any ket to return" << endl;
                            getch();
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << endl << "You entered a wrong code ";
            }
            cin.get();
            break;
        }
        case '3'://Resume trading
        {
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            Stock temp;
            if(cus[index].Administrator == 1)
            {
                system("cls");
                for(int i=0; i<100; i++)
                {
                    cout<< " ";
                }
                cout<< "The Stock System" <<endl;
                for(int i=0; i<237; i++)
                {
                    cout<< "~";
                }
                cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                     << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    Display_Stock_Market_Information(share, i, floatRange);
                }
                cin.get();
                temp.Start_Selling_Stock(share, cus, index);
                break;
            }
            else
            {
                cout << "You have not rights to resume the trading of the stock!" << endl;
                getch();
                break;
            }
        }
        case '4'://Stop trading
        {
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            Stock temp;
            if( cus[index].Administrator == 1 )
            {
                for(int i=0; i<100; i++)
                {
                    cout<< " ";
                }
                cout<< "The Stock System" <<endl;
                for(int i=0; i<237; i++)
                {
                    cout<< "~";
                }
                cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                     << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    Display_Stock_Market_Information(share, i, floatRange);
                }
                cin.get();
                temp.Close_Selling_Stock(share, cus, index);
                break;
            }
            else
            {
                cout << "You have not rights to stop the trading" << endl ;
                getch();
                break;
            }
        }
        case '5'://Modify datas
        {
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            Stock temp;
            if( cus[index].Administrator == 1 )
            {
                system("cls");
                for(int i=0; i<100; i++)
                {
                    cout<< " ";
                }
                cout<< "The Stock System" <<endl;
                for(int i=0; i<237; i++)
                {
                    cout<< "~";
                }
                cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                     << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    Display_Stock_Market_Information(share, i, floatRange);
                }
                cin.get();
                temp.Modify_Stock(share);
                break;
            }
            else
            {
                cout << "You have no rights to pause the trading of the stock" << endl;
                getch();
                break ;
            }
        }
        case '6'://Show the stock market
            time_t endtime = time(NULL);
            double floatRange[10] = {0};
            if (endtime - startTime >= 1)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;
                    floatRange[i] = result;

                    double original = share[i].currentPrice;
                    share[i].currentPrice = (1+result) * share[i].currentPrice;
                    if (original < share[i].currentPrice)//increase
                    {
                        share[i].color = 1;
                    }
                    else if (original > share[i].currentPrice)
                    {
                        share[i].color = 2;
                    }
                    else
                    {
                        share[i].color = 3;
                    }
                    Sleep(400);
                }
            }
            startTime = time(NULL);
            system("cls");
            for(int i=0; i<100; i++)
            {
                cout<< " ";
            }
            cout<< "The Stock System" <<endl;
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << endl << right << setw(30) << "Company Name" << setw(30) << "Company Code" << setw(30) << "Floating Stocks" << setw(30)
                 << "Stock Listed Price" << setw(30) << "Current Price" << setw(30) << "Status" <<endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                Display_Stock_Market_Information(share, i, floatRange);
            }
            for(int i=0; i<237; i++)
            {
                cout<< "~";
            }
            cout << right << setw(20) << "Market Value of Holding Stock" << setw(10) << "Money" << setw(20) << "Total Assets"<< endl;
            cus[index].Count_Total_Assets(share, cus, index);
            cout << right << setw(15) << cus[index].Holding_Market_Value << setw(22) << cus[index].Balance
                 << setw(17) << cus[index].Total_Assets << endl;

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\t\t\t\tStock you own" << endl << endl;
            cout << right << setw(20) << "Name" << setw(20) << "Code" << setw(20) << "Shares" << endl;

            for (int j=0; j<TOTALSTOCKS; j++)
            {
                if (cus[index].share_holding_name[j] == "$")//this means no name in the array
                {
                    continue;
                }
                else
                {
                    cout << right << setw(20) << cus[index].share_holding_name[j] << setw(20)
                         << cus[index].share_holding_code[j] << setw(20) << cus[index].share_holding_value[j] << endl;
                }
            }
            getch();
            break;
        }
        goto start;
    }
}

void Interface(vector <Stock> share, vector <Customer> cus)
{
    char choice;
    Stock temp;
    system("cls");
    cout << "***************The Stock System***************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Enter The Stock Market.....................[1]" << endl;
    cout << "Log In.....................................[2]" << endl;
    cout << "Register...................................[3]" << endl;
    cout << "Exit.......................................[0]" << endl;
    cout << endl;
    cout << endl << "Enter an option:";
    cin  >> choice;
    cout << "Please wait a second";
    Sleep(300);
    temp.Switch_choice(share, choice, cus);
}

void Stock::Switch_choice(vector <Stock> share, char choice, vector <Customer> cus)
{
    char pass_word[10];
    switch(choice)
    {
    case '0': //Exit
    {
        system("cls");
        cout << "Good Bye" << endl;
        StockWrite(share);
        CustomerWrite(cus);
        exit(0);
    }
    case '1': //Show the stock system
    {
        time_t endtime = time(NULL);
        double floatRange[10] = {0};
        if (endtime - startTime >= 1)
        {
            for (int i=0; i<TOTALSTOCKS; i++)//漲幅調整
            {
                srand(time(NULL));
                double x = rand() % 21 -10; //[-10, 10]
                double result = x * 0.01;
                floatRange[i] = result;

                double original = share[i].currentPrice;
                share[i].currentPrice = (1+result) * share[i].currentPrice;
                if (original < share[i].currentPrice)//increase
                {
                    share[i].color = 1;
                }
                else if (original > share[i].currentPrice)
                {
                    share[i].color = 2;
                }
                else
                {
                    share[i].color = 3;
                }
                Sleep(400);
            }
        }
        startTime = time(NULL);
        system("cls");
        for(int i=0; i<100; i++)
        {
            cout << " ";
        }
        cout << "The Stock System" << endl;
        for(int i=0; i<237; i++)
        {
            cout << "~";
        }
        cout << endl;
        cout << right << setw(20) << " "
             << left  << setw(30) << "Company Name"
             << left  << setw(30) << "Company Code"
             << left  << setw(30) << "Floating Stocks"
             << left  << setw(30) << "Stock Listed Price"
             << left  << setw(30) << "Current Price"
             << left  << setw(30) << "Status" <<endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            Display_Stock_Market_Information(share, i, floatRange);
        }
        for(int i=0; i<237; i++)
        {
            cout<< "~";
        }
        cout << endl << right
             << setw(20) << " " << "Hit any key to return";
        getch();
        Interface(share, cus);
        break;
    }
    case '2'://Log in with an exists account
    {
        int i = 0;
        string acc, pass;
        bool flag = 0;
        system("cls");
        cout << "***************The System Log In***************" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        cout << "Enter your Account : ";
        cin >> acc;
        for(i; i<cus.size(); i++)
        {
            if(acc == cus[i].Customer_Name)
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            cout << endl << "Not in the database" << endl << endl;
            cout << "Hit any key to return";
            getch();
            Interface(share, cus);
            break;
        }
        else
        {
            cout << "Enter your password: ";
            cin >> pass;
            int pass_Chance =3;
            while(pass != cus[i].Customer_Password)
            {
                pass_Chance--;
                if(pass_Chance!=0)
                {
                    system("cls");
                    cout << "Wrong password" << endl;
                    cout << "You have " << pass_Chance << " chances left" << endl;
                    cout << "Enter your password: ";
                    cin >> pass;
                }
                else
                {
                    cout << "You have entered the wrong password twice, returning" << endl;
                    cout << "Hit any key to return";
                    getch();
                    Interface(share, cus);
                    break;
                }
            }
            cout << "Sign in successfully" <<endl;
            cin.get();
            getch();
            cus[i].Stock_Portfolio(share, cus, i);
            break;
        }
    }
    case '3':// Register as a new user
    {
        Customer cust;
        system("cls");
        cout << "Registration" << endl;
        cout << "~~~~~~~~~~~~" << endl;
        cust.Register(cus);
    }
    default:
        system("cls");
        main();
    }
}

void Display_Stock_Market_Information(vector <Stock> share, int index, double floatRange[])
{
    string price;
    stringstream ss;
    ss.clear();
    ss.str("");

    cout << right << setw(20) << " "
         << left  << setw(30) << share[index].Stock_Name
         << left  << setw(30) << share[index].Stock_Code
         << left  << setw(30) << share[index].Free_Stocks_Float
         << left  << setw(30) << share[index].Stock_Listed_Price;

    if(share[index].color == 1)//red
    {
        ss << share[index].currentPrice << "(+" << floatRange[index] * 100 << "%)";
        ss >> price;
        ss.clear();
        ss.str("");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//change red color
        cout << left << setw(30) << price;
    }
    else if(share[index].color == 2)//green
    {
        ss << share[index].currentPrice << '(' << floatRange[index] * 100 << "%)";
        ss >> price;
        ss.clear();
        ss.str("");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//change green color
        cout << left << setw(30) << price;
    }
    else//No change
    {
        cout << left << setw(30) << share[index].currentPrice << '(' << floatRange[index] * 100 << "%)";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white
    cout << left << setw(30) << (share[index].Close_Selling == 0?"Trading Not Stopped":"Trading Stopped") << endl;
}

void Stock::Close_Selling_Stock(vector <Stock> &share, vector <Customer> cus, int index)//Stop trading
{
    int flag;
    char input;
    string share_code = "";
    Customer cust;
    cout<<"Enter to stock code you want to stop trading: (Enter 0 to return)";
    cin >> share_code;
    if (share_code == "0")
    {
        cust.Stock_Portfolio(share, cus, index);
    }

    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the stock code you want to stop trading: (Enter 0 to return)";
        cin >> share_code;
        if (share_code == "0")
        {
            cust.Stock_Portfolio(share, cus, index);
        }
    }
    int i=0;
    flag = 0;
    if( share_code != "")
    {
        while( (i<TOTALSTOCKS) && (!flag) )
        {
            if(share[i].Stock_Code == share_code)
            {
                flag = 1;
                cout << "Confirm(y/n)";
                cin >> input;
                if(input == 'y')
                {
                    share[i].Close_Selling = 1;
                    StockWrite(share);
                    cout << "Stopped" << endl;
                    cout << endl;
                    break;
                }
                else if(input=='n')
                {
                    cout << "Canceled" << endl;
                }
                else
                {
                    cout << "Wrong option" <<endl;
                }
            }
            else i++;
            if(i == TOTALSTOCKS)
            {
                cout << "Wrong code" << endl;
                break;
            }
        }
    }
    getch();
}

void Stock::Start_Selling_Stock(vector <Stock> &share,vector <Customer> cus, int index) //Resume trading
{
    char input;
    int flag;
    Customer cust;
    string share_code = "";
    cout << "Enter the stock code you want to resume trading: (Enter 0 to return)";
    cin >> share_code;
    if (share_code == "0")
    {
        cust.Stock_Portfolio(share, cus, index);
    }
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the stock code you want to resume trading: (Enter 0 to return)";
        cin >> share_code;
        if (share_code == "0")
        {
            cust.Stock_Portfolio(share, cus, index);
        }
    }
    int i= 0;
    flag = 0;
    while( (!flag) && (i<TOTALSTOCKS) )
    {
        if( share[i].Stock_Code == share_code )
        {
            flag = 1;
            cout << "Confirm(y/n)";
            cin >> input;
            if(input == 'y')
            {
                share[i].Close_Selling = 0;
                StockWrite(share);
                cout << "Resumed" << endl;
                cout << endl;
                break;
            }
            else if(input == 'n')
            {
                cout << "Canceled" << endl;
            }
            else
            {
                cout << "Wrong option" <<endl;
            }
        }
        else i++;
        if(i == TOTALSTOCKS)
        {
            cout << "Wrong code" << endl;
            break;
        }
    }
    getch();
}

void Stock::Modify_Stock(vector <Stock> &t)
{
    int flag;
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "Enter the original code" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the original code:";
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
                    cout<<"The trading has been stopped"<<endl;
                    break;
                }
                else
                {
                    cin.clear();
                    flag = 1;
                    cout << "Enter new name (below 20 characters)" << endl;
                    cin >> share_name;
                    while (share_name.size() > 20 || share_name.size() <= 0)
                    {
                        cout << "The name has to be less than 20 characters or 1 above" << endl;
                        cout << "Enter new name (below 20 characters)";
                        cin >> share_name;
                    }
                    t[i].Stock_Name = share_name;
                    cin.get();
                    cout << "Enter new code (below 5 characters)";
                    cout << endl;
                    cin >> share_code;
                    while (share_code.size() > 5 || share_code.size() <= 0)
                    {
                        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
                        cout << "Enter the new code:";
                        cin >> share_code;
                    }
                    t[i].Stock_Code = share_code;
                    StockWrite(t);
                }
            }
            else
            {
                i++;
            }
            if(i==TOTALSTOCKS)
            {
                cout << "The stock doesn't exist" << endl;
                cout << "Hit any key to return" << endl;
                getch();
            }
        }
    }
    else
    {
        cout << "Wrong format";
    }
}

void StockWrite(vector <Stock> share)
{
    ofstream dataFile("Stock_File.txt");
    if (!dataFile)
    {
        cout << "Can not open Stock_file.txt" << endl;
    }
    else
    {
        for (int i=0; i<share.size(); i++)
        {
            dataFile << share[i].Stock_Name << ' ' << share[i].Stock_Code << ' '
                     << share[i].Free_Stocks_Float << ' '
                     << share[i].Stock_Listed_Price << ' '
                     << share[i].Market_Value << ' ' << share[i].currentPrice << ' ' << share[i].Close_Selling << endl;
        }
    }
}

void CustomerWrite(vector <Customer> cus)
{
    ofstream file("Customer.txt");
    if(!file)
    {
        cout<< "Can not open Customer_file.txt" << endl;
    }
    else
    {
        for(int i=0; i<cus.size(); i++)
        {
            file << cus[i].Customer_Name << ' ' << cus[i].Customer_Password << ' ';
            for(int j=0; j<10; j++)
            {
                file << cus[i].share_holding_name[j] << ' ';
            }
            file << "|" << ' ';
            for(int j=0; j<10; j++)
            {
                file << cus[i].share_holding_code[j] << ' ';
            }
            file << "|" << ' ';
            for(int j=0; j<10; j++)
            {
                file << cus[i].share_holding_value[j] << ' ';
            }
            file << "|" << ' ';
            file << cus[i].Balance << ' ' << cus[i].Holding_Market_Value << ' ' << cus[i].Total_Assets << ' ' << cus[i].Administrator <<endl;
        }
    }
    file.close();
}

int main()
{
    ifstream dataFile("Stock_File.txt");
    vector <Stock> share;

    if (!dataFile)
    {
        cout << "Can not open Stock_file.txt" << endl;
    }
    else
    {
        unsigned long long freefloat;
        string name, code;
        double value, currentPrice, listedPrice;
        bool close;
        while (dataFile >> name >> code >> freefloat >> listedPrice >> value >> currentPrice >> close)
        {
            Stock tmp(name, code, freefloat, listedPrice, value, currentPrice, close);
            share.push_back(tmp);
        }
    }
    dataFile.close();

    vector <Customer> Cus;
    ifstream file("Customer.txt");
    if(!file)
    {
        cout<< "can't open the txt" <<endl;
    }
    else
    {
        string name, pass, share_holding_name, share_holding_code, share_holding_value;
        double Balance, Holding_Market_Value, Total_Assets;
        bool Administrator;

        while(file >> name >> pass)
        {
            vector <string> ShareHoldingName, ShareHoldingCode;
            vector <double>ShareHoldingValue;

            while(file >> share_holding_name && share_holding_name != "|")
            {
                ShareHoldingName.push_back(share_holding_name);
            }

            while(file >> share_holding_code && share_holding_code !="|")
            {
                ShareHoldingCode.push_back(share_holding_code);
            }

            while(file >> share_holding_value && share_holding_value != "|")
            {
                double SHV = stod(share_holding_value);
                ShareHoldingValue.push_back(SHV);
            }

            file >> Balance >> Holding_Market_Value >> Total_Assets >> Administrator;

            Customer t(name, pass, ShareHoldingName, ShareHoldingCode, ShareHoldingValue, Balance,
                       Holding_Market_Value, Total_Assets, Administrator);

            Cus.push_back(t);
        }
    }
    file.close();

    time_t startTime;
    startTime = time(NULL);
    Interface(share, Cus);
}
