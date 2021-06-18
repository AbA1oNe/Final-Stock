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

const int TOTALSTOCKS = 10;//how many stocks
int flag;
double Random();// function that controls the float
int main();

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Stock_Volume;    //�Ѳ��`�Ѽ�   //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    unsigned long long Free_Stocks_Float;//�ۥѬy�q�ѥ� //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    long long int The_Share_Volume_Of_Stocks;//�Ѳ�����q
    string Stock_Name;            //�Ѳ��W��
    string Stock_Code;             //�Ѳ��N�X
    double Stock_Issue_Price;       //�Ѳ��o���
    double Stock_Listed_Price;      //�Ѳ��W����
    double Market_Value;            //�Ѳ�����         //����
    double openingPrice;            //�}�L��       //����
    double closingPrice;            //���L��       //����
    double currentPrice;            //�R���       //����
    bool Close_Selling;             //�O�_�Ȱ�����Ҩ�]1���O�A0���_�^//�쥻�i�H�Ĩ骺�Ѳ��A�Ȯɤ���A�H�Ĩ��X�C//Short_Selling_Suspended
    int color;                      //�C��
public:
    Stock(string name = "", string code = "", unsigned long long volume = 0,unsigned long long freefloat = 0, double issuePrice = 0, double listedPrice = 0, double value = 0, double openPrice = 0, double closePrice = 0, double currentPrice = 0, bool close = 0)
    {
        Stock_Name = name;
        Stock_Code = code;
        Stock_Volume = volume;
        Free_Stocks_Float = Stock_Volume;//��l�ۥѬy�q�ѥ�
        Stock_Issue_Price = issuePrice;
        Stock_Listed_Price = listedPrice;
        Market_Value = value;
        openingPrice = openPrice;
        closingPrice = closePrice;
        currentPrice = currentPrice;
        Close_Selling = close;
        color = 0;
    }
    void Close_Selling_Stock(vector <Stock>); //�Ȱ��Ѳ����
    void Start_Selling_Stock(vector <Stock>); //��_�Ѳ����
    void Modify_Stock(vector <Stock>);//�ק�Ѳ����(�޲z��)

    void Display_Stock_Market_Information();//��ܫH��
    void Switch_choice(vector <Stock>, char, time_t ,vector <Customer>);//�\����
    friend void Save(vector <Stock>);         //�O�s�ק�
};

void Interface(vector <Stock>, time_t, vector <Customer>);

class Customer
{
    friend class Stock;
private:
    double share_holding_value[10] = {0};   //�����Ѳ��ƶq
    string Customer_Name;                   //�Τ�W
    string Customer_Password;               //�K�X
    string share_holding_name[10] = {""};   //�����Ѳ��W��
    string share_holding_code[10] = {""};   //�����Ѳ��N�X

    double Balance;                         //�{���l�B
    double Holding_Market_Value;            //�����Ѳ�����
    double Total_Assets;                    //�`�겣
    bool Administrator;                     //�O�_�޲z��
public:
    Customer(string CusName = "", string CusPass = "", vector <string> VHoldName = {""},
             vector <string> VHoldCode = {""}, vector <double> VHoldValue = {0},
             double B = 0, double HMV = 0, double TA = 0, bool Admin = 0)
    {
        Customer_Name = CusName;
        Customer_Password = CusPass;
        for(int i=0; i<VHoldName.size(); i++) {
            share_holding_name[i] = VHoldName[i];
        }
        for(int i=0; i<VHoldCode.size(); i++) {
            share_holding_code[i] = VHoldCode[i];
        }
        for(int i=0; i<VHoldValue.size(); i++) {
            share_holding_value[i] = VHoldValue[i];
        }
        Balance = B;
        Holding_Market_Value = HMV;
        Total_Assets = TA;
        Administrator = Admin;
    }
    void Log_In(string, vector <Stock>, time_t) const;//�n��
    void Register(Customer *);//���U
    void Stock_Portfolio(vector <Stock>, time_t, vector <Customer>, int ) const; // �����Ҩ�
    //friend void Switch_choice(vector <Stock>, char, time_t);
};
Stock temp;//�����ܶq�A�n���Ѳ���H
Customer cust;//�n���Τ��H�A�����ܶq


/*void Customer::Log_In(string pass_word, vector <Stock> share, time_t startTime) const//�n��
{
    if( pass_word == Customer_Password )//�ֹ�K�X
    {
        Stock_Portfolio(share, startTime,);
    }
    else
    {
        cout << endl;
        cout << "Wrong password"<<endl;
    }
}*/

void Customer::Register(Customer *cust)//���U
{
    char input;
    system("cls");
    cin.get();
    cout << "Welcome to---------------The Stock System---------------" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please enter your username: ";
    cin >> Customer_Name;
    cout << "Please enter your password:" << endl;
    cin >> Customer_Password;
    while (Customer_Password.size() <= 0 || Customer_Password.size() > 8)
    {
        cout << "The password has to be less than 8 characters and 1 above" << endl;
        cout << "Please enter your password:" << endl;
        cin >> Customer_Password;
    }

    cout << endl;
    cout << "Please enter your starting money";
    cin >> Total_Assets;
    Holding_Market_Value = 0;
    Balance = Total_Assets;
    cout << "Administrator or not?(y/n)" << endl;//�j�p�g����
    cin >> input;
    if( (input == 'y') || (input == 'Y') )
    {
        Administrator = 1;
        cout << "Set!";
    }
    else if( (input == 'n') || (input == 'N') )
    {
        Administrator = 0;
    }
    else
    {
        cout << "Default as not a admin";
    }
    getch();
    system("cls");//�M��
    cout << "Done!"     << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Hit any key to return" << endl;
    getch();
}

void Customer::Stock_Portfolio(vector <Stock> share, time_t startTime, vector <Customer> cus, int index) const//�Τ����ާ@�����t��
{
    int i,a;
    char input;
    string code;
    long int volume;
start:
    system("cls");
    cout << endl << endl;
    cout << "\t\tWelcome to---------------The Stock System---------------" << endl;
    cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t User: " << cust.Customer_Name << endl << endl;
    cout << "\t\t Buy..........................[1]" << endl;
    cout << "\t\t Sell..........................[2]" << endl;
    cout << "\t\t Resume a stock's trading..................[3]" << endl;
    cout << "\t\t Pause a stock's trading..................[4]" << endl;
    cout << "\t\t Modify a stock's name or code............[5]" << endl;//?i?H?A?s?W?n???
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
        case '0'://��^�D����
        {
            main();
        }
        case '1': //�R�J
        {
            time_t endtime = time(NULL);
            for (int j=0; j<(endtime - startTime) / 10; j++)
            {
                for (int i=0; i<TOTALSTOCKS; i++)
                {
                    srand(time(NULL));
                    double x = rand() % 21 -10; //[-10, 10]
                    double result = x * 0.01;

                    double original = share[i].Stock_Listed_Price;
                    share[i].Stock_Listed_Price = (1+result) * share[i].Stock_Listed_Price;
                    if (original < share[i].Stock_Listed_Price)//��
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
            cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                share[i].Display_Stock_Market_Information();//��ܥ����H��
            }
            cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Market Value of Holding Stock\tMoney\tTotal Assets" << endl;
            cout << cust.Holding_Market_Value
                 << "\t\t" << cust.Balance
                 << "\t\t" << cust.Total_Assets << endl;
            cin.get();
            cout << endl << "Enter the stock code you want to buy:";
            cin >> code;

            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "Stock code has to be less than 5 characters or 1 above" << endl;
                cout << "Enter the stock code you want to buy:";
                cin >> code;
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
                            int Max_Buy_Stock_Volume;//�{���l�B�i�R�Ѽ�
                            Max_Buy_Stock_Volume = int(cust.Balance/share[i].Stock_Listed_Price);//����
                            cout << "At most you can buy:" << Max_Buy_Stock_Volume << endl;
                            flag = 1;
                            cout << "Enter how much you want to buy: ";
                            cin >> volume;
                            while(volume != (int)volume)//�P�_��J�O�_�����
                            {
                                cout<<"Please enter an integer"<<endl;
                                cin >> volume;
                            }
                            if( (share[i].Free_Stocks_Float >= volume) && (cust.Balance >= volume*share[i].Stock_Listed_Price) )
                            {
                                //��ʦU�ƾ�
                                cust.share_holding_value[i] += volume;
                                cust.share_holding_name[i] = share[i].Stock_Name;
                                cust.share_holding_code[i] = share[i].Stock_Code;

                                share[i].Free_Stocks_Float -= volume;
                                cust.Balance -= share[i].Stock_Listed_Price*volume;
                                cust.Holding_Market_Value += share[i].Stock_Listed_Price*volume;
                                system("cls");
                                cout << "Done" << endl;
                                cout << endl;
                                cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
                                for(i=0; i < TOTALSTOCKS; i++)
                                {
                                    cout << " " << share[i].Stock_Name
                                         << "\t" << share[i].Stock_Code
                                         << "\t" << share[i].Stock_Volume
                                         << "\t" << cust.share_holding_value[i]
                                         << "\t" << share[i].Stock_Issue_Price
                                         << "\t " << share[i].Stock_Listed_Price
                                         << " \t " << (share[i].Close_Selling == 0 ?"Trading Not Stopped":"Trading Stopped") << endl;
                                }
                                cout << "Market Valuse of Holding Stock\tMoney\tTotal Assets"  << endl;
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
                                cout << share[i].Stock_Name << "has less stocks than you want to buy";
                                cout << endl;
                                cout << "Hit any key to return" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                            else if(cust.Balance <= volume*share[i].Stock_Listed_Price)
                            {
                                cout << "Not enough money";
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
                        while(i == TOTALSTOCKS)
                        {
                            system("cls");
                            cout << "Wrong code" << endl;
                            cout << "Hit any ket to return" << endl;
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << "Wrong format" << endl;
                cout << "Hit any key to return" << endl;
            }
            cin.get();
            break;
        }
        case '2':
        {
            //��X�Ѳ�
            system("cls");
            cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
            for(i=0; i < TOTALSTOCKS; i++)
            {
                cout << " " << share[i].Stock_Name
                     << "\t" << share[i].Stock_Code
                     << "\t" << share[i].Stock_Volume
                     << "\t" << cust.share_holding_value[i]
                     << "\t" << share[i].Stock_Issue_Price
                     << "\t " << share[i].Stock_Listed_Price
                     << " \t " << (share[i].Close_Selling == 0 ?"Trading Not Stopped":"Trading Stopped") << endl;
            }
            cout << "\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Market Value of Holding Stock\tMoney\tTotal Assets" << endl;
            cout << cust.Holding_Market_Value << "\t\t" << cust.Balance << "\t\t" << cust. Total_Assets << endl;
            cin.get();
            cout << endl << "Enter the stock code you want to sell: ";
            code = "";
            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "Stock code has to be less than 5 characters or 1 above" << endl;
                cout << "Enter the stock code you want to buy:";
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
                            cout << "The stock has paused trading" << endl;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            cout << "Enter how much you want to sell: ";
                            cin >> volume;
                            while(volume != (int)volume)//?P?_??J?O?_?????
                            {
                                cout<<"Please enter an integer"<<endl;
                                cin >> volume;
                            }
                            if(cust.share_holding_value[i] >= volume)
                            {
                                cust.share_holding_value[i] -= volume;
                                share[i].Free_Stocks_Float += volume;
                                cust.Balance += share[ i].Stock_Listed_Price*volume;
                                cust.Holding_Market_Value -= share[i].Stock_Listed_Price*volume;
                                system("cls");
                                cout << "Done" << endl;
                                cout << endl;
                                ofstream data(cust.Customer_Name,ios::binary);
                                data.write((char*)(&cust),sizeof(cust));
                                Save(share);
                            }
                            else
                            {
                                cout << "You don't have enought stocks to sell";
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
                        while(i == TOTALSTOCKS)
                        {
                            system("cls");
                            cout << "You didn't buy the stock" << endl;
                            cout << "Hit any key to return";
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
        case '3'://��_�Ѳ����
        {
            if(cust.Administrator == 1)
            {
                system("cls");
                cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//��ܥ����H��
                }
                cin.get();
                temp.Start_Selling_Stock(share);
                break;
            }
            else
            {
                cout << "You have not rights to resume the trading of the stock!" << endl;
                getch();
                break;
            }
        }
        case '4'://����Ѳ�
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//��ܥ����H��
                }
                cin.get();
                temp.Close_Selling_Stock(share);//�i��
                break;
            }
            else
            {
                cout << "You have not rights to hang the stock" << endl ;
                getch();
                break;
            }
        }
        case '5'://�ק�Ѳ�
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
                for(int i=0; i < TOTALSTOCKS; i++)
                {
                    share[i].Display_Stock_Market_Information();//��ܥ����H��
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
        case '6'://�d�ݫH��
            system("cls");
            cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
            for(int i=0; i<TOTALSTOCKS; i++)
            {
                cout << " "   << share[i].Stock_Name
                     << "\t\t" << share[i].Stock_Code
                     << "\t\t" << share[i].Stock_Volume
                     << "\t\t" << cust.share_holding_value[i]
                     << "\t\t" << share[i].Stock_Issue_Price
                     << "\t\t" << share[i].Stock_Listed_Price
                     << "\t\t" << (share[i].Close_Selling == 0?"Trading Not Stopped":"Trading Stopped") << endl;

            }
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Market Value of Holding Stock\t\tMoney\tTotal Assets"<<endl;
            cout << " " << cust.Holding_Market_Value
                 << "\t\t\t" << cust.Balance
                 << "\t\t" << cust.Total_Assets << endl;
            getch();
            break;
        }
        goto start;
    }
}

void Interface(vector <Stock> share, time_t startTime, vector <Customer> cus)
{
    char choice;
    system("cls");
    cout << "***************The Stock System***************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Enter The Stock Market................[1]" << endl;
    cout << "Log In........................[2]" << endl;
    cout << "Register......................[3]" << endl;
    cout << "Exit......................[0]" << endl;
    cout << endl << endl;
    cout << endl << "Enter an option:";
    cin >> choice;
    switch (choice)
    {
    case '1':
    case '2':
    case '3':
    case '0':
        temp.Switch_choice(share, choice, startTime, cus);
    default:
        system("cls");
        main();
    }
}

void Stock::Switch_choice(vector <Stock> share, char choice, time_t startTime, vector <Customer> cus)
{
    char pass_word[10];
    switch(choice)
    {
    case '0': //�N�h�X
    {
        system("cls");
        cout << "Good Bye" << endl;
        exit(0);
    }
    case '1': //�i�J�Ѳ��������
    {
        time_t endtime = time(NULL);
        for (int j=0; j<(endtime - startTime) / 10; j++)
        {
            for (int i=0; i<TOTALSTOCKS; i++)
            {
                srand(time(NULL));
                double x = rand() % 21 -10; //[-10, 10]
                double result = x * 0.01;

                double original = share[i].Stock_Listed_Price;
                share[i].Stock_Listed_Price = (1+result) * share[i].Stock_Listed_Price;
                if (original < share[i].Stock_Listed_Price)//��
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
        cout << "\t\t\t------------------------------The Stock System------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " Company Name\t\tCompany Code\tFloating Stocks\t\tShare-holding Stock\t\tStock Issue Price\t\tStock Listed Price\t\tStatus" << endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share[i].Display_Stock_Market_Information();//��ܥ����T��
        }
        cin.get();
        getch();
        main();
        break;
    }
    case '2'://�n���Τ�
    {
        int i = 0;
        string acc, pass;
        bool flag = 0;
        system("cls");
        cout << "\n\n\t\t***************The Stock System**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter your Account: ";
        cin >> acc;
        for(i; i<cus.size(); i++) {
            if(acc == cus[i].Customer_Name) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            cout << "Not in the database" << endl;
            getch();
            main();
        }
        else {
            cout<< "Enter your password: ";
            cin>>pass;
            while(pass != cus[i].Customer_Password) {
                system("cls");
                cout<< "Wrong password" <<endl;
                cout<< "Enter your password: ";
                cin>>pass;
            }
            cout << "Sign in suceesfully" <<endl;
            cin.get();
            cust.Stock_Portfolio(share, startTime, cus, i);
            break;
        }
        /*ifstream read_customer(cust.Customer_Name);//Ū�w���ƾ�//�n�A�ק�
        while( !read_customer.eof() )//�P�_�O�_���O��
        {
            read_customer.read((char*)(&cust),sizeof(cust));
            if( read_customer.fail() )
            {
                cout << endl;
                cout << "Not in the database" << endl;
                getch();
                main();
            }
            else
            {
                cout << "�Τ�K�X:";
                char input;
                int i=0;
                cout << "��J�K�X:"<<endl;
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
                    cout << endl << "Wrong password";
                }
                read_customer.close();
                cin.get();
                break;
            }
        }*/
    }
    case '3':  //���U�s�Τ�
    {
        system("cls");
        cout << "Registration" << endl;
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
         << "\t\t" << (Close_Selling == 0?"Trading Not Stopped":"Trading Stopped") << endl;
}

void Stock::Close_Selling_Stock(vector <Stock> share)//�Ȱ��Ѳ����
{
    char input;
    string share_code = "";
    cout<<"Enter to stock code you want to stop trading";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the stock code you want to buy:";
        cin >> share_code;
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
                    Save(share);
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

void Stock::Start_Selling_Stock(vector <Stock> share)//��_�Ѳ����
{
    char input;
    string share_code = "";
    cout << "Enter the stock code you want to resume trading:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the stock code you want to buy:";
        cin >> share_code;
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
                Save(share);
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

void Stock::Modify_Stock(vector <Stock> t)//�վ��T
{
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "Enter the original code" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "Stock code has to be less than 5 characters or 1 above" << endl;
        cout << "Enter the stock code you want to buy:";
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
                        cout << "�Ѳ��W�ٻݤp��20�r���Φܤ֦��@�Ӧr��" << endl;
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
                        cout << "Enter the stock code you want to buy:";
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
                cout << "The stock doesn't exist" << endl;
                cout << "Hit any key to return" << endl;
                getch();
            }
        }
    }
    else
    {
       cout << "��J���~!";
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

    vector <Customer> Cus;
    ifstream file("Customer.txt");
    if(!file) {
        cout<< "can't open the txt" <<endl;
    }
    else {
        string name, pass, share_holding_name, share_holding_code, share_holding_value;
        double Balance, Holding_Market_Value, Total_Assets;
        bool Administrator;

        while(file >> name >> pass) {
            vector <string> ShareHoldingName, ShareHoldingCode;
            vector <double>ShareHoldingValue;

            while(file >> share_holding_name && share_holding_name != "|") {
                ShareHoldingName.push_back(share_holding_name);
            }

            while(file >> share_holding_code && share_holding_code !="|") {
                ShareHoldingCode.push_back(share_holding_code);
            }

            while(file >> share_holding_value && share_holding_value != "|") {
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
    Interface(share, startTime, Cus);
}
