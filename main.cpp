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

const int TOTALSTOCKS = 10;//�]�w����X�ӪѲ������
//int Num_Of_Stock;//�{���Ѳ������ƶq�A�p�ƥ�
int flag;
int getTime();      //�Ѳ��B�ʤ��@Function
double Random();    //�Ѳ��B�ʤ��@Function

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Stock_Volume;    //�Ѳ��`�Ѽ�   //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    unsigned long long Free_Stocks_Float;//�ۥѬy�q�ѥ� //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    //�p�G�Ounsigned long long �O 0 �� 18,446,744,073,709,551,615
    long long int The_Share_Volume_Of_Stocks;//�Ѳ�����q //����
    string Stock_Name;            //�Ѳ��W��     //�i�H���r��
    string Stock_Code;             //�Ѳ��N�X     //�i�H���r��
    double Stock_Issue_Price;       //�Ѳ��o���
    double Stock_Listed_Price;      //�Ѳ��W����
    double Market_Value;            //�Ѳ�����         //����
    double openingPrice;            //�}�L��       //����
    double closingPrice;            //���L��       //����
    double currentPrice;            //�R���       //����
    bool Close_Selling;             //�O�_�Ȱ�����Ҩ�]1���O�A0���_�^//�쥻�i�H�Ĩ骺�Ѳ��A�Ȯɤ���A�H�Ĩ��X�C//Short_Selling_Suspended
    int color;                      //����1(�^), ���2(��), �զ�0(����)
public:
    Stock(string name = "", string code = "", unsigned long long volume = 0,unsigned long long freefloat = 0, double issuePrice = 0, double listedPrice = 0, double value = 0, double openPrice = 0, double closePrice = 0, double currentPrice = 0, bool close = 0)
    {
        //Num_Of_Stock = 0;//�{���Ѳ������ƶq�A�p�ƥ�
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
    void Delete_Stock();        //�R���Ѳ�(�޲z��)
    void Add_New_Stock();       //�[�J�s�Ѳ�(�޲z��)

    void Display_Stock_Market_Information();//��ܫH��
    friend void Switch_choice(vector <Stock>, char);       //�\����
    void Market_Analysis();     //�������R
    friend void Save(vector <Stock>);         //�O�s�ק�
//-----------------------------------------------------------------��111����
    friend void Display_Stock_Market_Information(int );//receive option number+1 if -1, then it's display all info
    /*�i�ܦU���ѥ��H��
    (
    1.�}�L���GOpening Price
    2.���L���GClosing Price
    3.�����GLimit Up
    4.�^���GLimit Down
    5.���� : Price
    ......��
    )
    */
    void setEverything(char*, char*, int, double, double, double, long long, long long, long long, long long, long long);
    friend void Write_File();//�g��
    //�H�U����private data
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

    bool checkFloat();//�ˬd�B�� �p�G���htrue
    void randomChange(vector <Stock>);//�H�ɶ����ܥثe������
};

/*void Stock::setEverything(char* name, char* code, int update, double issue, double listed, double market, long long floatStock, long long shareVolume, long long opening, long long closing, long long current)
{
    //�]�wclass��private data
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
//--------------------------------------------------------------------��o��

void Interface(vector <Stock>);//�������

class Customer
{
    friend class Stock;
private:
    unsigned long int share_holding_value[10];//�����Ѳ��ƶq
    string Customer_Name;//�Τ�W
    string Customer_Password;//�K�X
    string share_holding_name[10];//�����Ѳ��W��
    string share_holding_code[10];//�����Ѳ��N�X

    double Balance;//�{���l�B
    double Holding_Market_Value;//�����Ѳ�����
    double Total_Assets;//�`�겣
    bool Administrator;//�O�_�޲z��
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
    void Log_In(string, vector <Stock>) const;//�n��
    void Register(Customer *);//���U
    void Stock_Portfolio(vector <Stock>) const; // Portfolio--�����Ҩ�
    friend void Switch_choice(vector <Stock>, char);
    //----------------------------------------------------------------------------------��151����
    /*
    void buy();//�R
    void sell();//��
    string getName();
    string getPass();
    holdingStock getHoldingStock();
    double getBalance();
    double getTotalAsset();
    bool getAdmin();
    */
    //-----------------------------------------------------------------------------------��o�̳�
};
Stock temp;//�����ܶq�A�n���Ѳ���H
Customer cust;//�n���Τ��H�A�����ܶq


void Customer::Log_In(string pass_word, vector <Stock> share) const//�n��
{
    if( pass_word == Customer_Password )//�ֹ�K�X
    {
        Stock_Portfolio(share);
    }
    else
    {
        cout << endl;
        cout << "�K�X���~"<<endl;
    }
}

void Customer::Register(Customer *cust)//���U�b��
{
    char input;
    system("cls"); //����t�ΩR�O�G�M��=cls
    cin.get();
    cout << "�w��i�J---------------�Ѳ��t��---------------" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "�п�J�b��/�Τ�W: ";
    cin >> Customer_Name;
    cout << "�п�J�K�X(�֩�8�r): " << endl;
    cin >> Customer_Password;
    while (Customer_Password.size() <= 0 || Customer_Password.size() > 8)
    {
        cout << "��J���~" << endl;
        cout << "�п�J�K�X(�֩�8�r): " << endl;
        cin >> Customer_Password;
    }

    cout << endl;
    cout << "��J�z����l���:";
    cin >> Total_Assets;
    Holding_Market_Value = 0;
    Balance = Total_Assets;
    cout << "�O�_�]���޲z��?(y/n)" << endl;//�j�p�g����
    cin >> input;
    if( (input == 'y') || (input == 'Y') )
    {
        Administrator = 1;
        cout << "�w�]�w";
    }
    else if( (input == 'n') || (input == 'N') )
    {
        Administrator = 0;
    }
    else
    {
        cout << "�q�{���D�޲z��";
    }
    getch();
    system("cls");//�M��
    cout << "�w�g�������U"     << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "�����N���^" << endl;
    getch();
}

void Customer::Stock_Portfolio(vector <Stock> share) const//�Τ����ާ@�����t��
{
    int i,a;
    char input;
    string code;
    long int volume;
start:
    system("cls");
    cout << endl << endl;
    cout << "\t\t�w��ϥ�---------------�Ѳ��t��---------------" << endl;
    cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t �Τ�: " << cust.Customer_Name << endl << endl;
    cout << "\t\t �R�J..........................[1]" << endl;
    cout << "\t\t ��X..........................[2]" << endl;
    cout << "\t\t ��_�Ѳ����..................[3]" << endl;
    cout << "\t\t �Ȱ��Ѳ����..................[4]" << endl;
    cout << "\t\t �ק�Ѳ��N�X�ΦW��............[5]" << endl;//�i�H�A�s�W�n�ק諸
    cout << "\t\t �d�ݪѥ���T..................[6]" << endl;
    cout << "\t\t �h�X�b��......................[0]" << endl;
    cout << endl << "\t\t ��J�\��ﶵ: ";

    cin >> input;

    if( (input>'6') || (input<'0') )
        goto start;
    else
    {
        switch(input)
        {
        case '0'://��^�D����
        {
            Interface(share);
        }
        case '1': //�R�J
        {
            system("cls");
            cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                share[i].Display_Stock_Market_Information();//��ܥ����H��
            }
            cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " �����Ѳ�����\t�i�θ��\t�`�겣" << endl;
            cout << cust.Holding_Market_Value
                 << "\t\t" << cust.Balance
                 << "\t\t" << cust.Total_Assets << endl;
            cin.get();
            cout << endl << "��J�z�n�ʶR���Ѳ��N�X:";
            cin >> code;

            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
                cout << "��J�z�n�ʶR���Ѳ��N�X:";
                cin >> code;
            }

            if( code != "" )//���J�^���ɳ���
            {
                int i = 0;
                flag = 0;
                while( (i < TOTALSTOCKS) && (!flag) )
                {
                    if ( code == share[i].Stock_Code)
                    {
                        if( share[i].Close_Selling == 1 )
                        {
                            cout << "�Ѳ��w�Ȱ����!" << endl;
                            break;
                        }
                        else
                        {
                            int Max_Buy_Stock_Volume;//�{���l�B�i�R�Ѽ�
                            Max_Buy_Stock_Volume = int(cust.Balance/share[i].Stock_Listed_Price);//����
                            cout << "�z�̦h�i�ʶR�q:" << Max_Buy_Stock_Volume << endl;
                            flag = 1;
                            cout << "��J�ݭn�ʶR�q: ";
                            cin >> volume;
                            while(volume != (int)volume)//�P�_��J�O�_�����
                            {
                                cout<<"��J���~,�Э��s��J(���)"<<endl;
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
                                cout << "�������" << endl;
                                cout << endl;
                                cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
                                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                                cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
                                for(i=0; i < TOTALSTOCKS; i++)
                                {
                                    cout << " " << share[i].Stock_Name
                                         << "\t" << share[i].Stock_Code
                                         << "\t" << share[i].Stock_Volume
                                         << "\t" << cust.share_holding_value[i]
                                         << "\t" << share[i].Stock_Issue_Price
                                         << "\t " << share[i].Stock_Listed_Price
                                         << " \t " << (share[i].Close_Selling == 0 ?"������":"�w����") << endl;
                                }
                                cout << "�����Ѳ�����\t�i�θ��\t�ثe�`�겣"  << endl;
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
                                cout << share[i].Stock_Name << "���i�ʪѲ��ƶq�֩�z�һݭn�Ѳ��ƶq";
                                cout << endl;
                                cout << "�����N���^" << endl;
                                cout << endl;
                                getch();
                                system("cls");
                                goto start;
                            }
                            else if(cust.Balance <= volume*share[i].Stock_Listed_Price)
                            {
                                cout << "�i�θ������!";
                                cout << "�����N���^" << endl;
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
                            cout << "��J�N�X���~" << endl;
                            cout << "�����N���^" << endl;
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << "��J�榡���~" << endl;
                cout << "�����N���^" << endl;
            }
            cin.get();
            break;
        }
        case '2':
        {
            //��X�Ѳ�
            system("cls");
            cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
            for(i=0; i < TOTALSTOCKS; i++)
            {
                cout << " " << share[i].Stock_Name
                     << "\t" << share[i].Stock_Code
                     << "\t" << share[i].Stock_Volume
                     << "\t" << cust.share_holding_value[i]
                     << "\t" << share[i].Stock_Issue_Price
                     << "\t " << share[i].Stock_Listed_Price
                     << " \t " << (share[i].Close_Selling == 0 ?"������":"�w����") << endl;
            }
            cout << "\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " �����Ѳ�����\t�i�θ��\t�ثe�`�겣" << endl;
            cout << cust.Holding_Market_Value << "\t\t" << cust.Balance << "\t\t" << cust. Total_Assets << endl;
            cin.get();
            cout << endl << "��J���Ѳ��N�X: ";
            code = "";
            while (code.size() > 6 || code.size() <= 0)
            {
                cout << "�Ѳ��N�X�����j��6�X�Φܤ֦�1�X" << endl;
                cout << "��J�z�n�ʶR���Ѳ��N�X:";
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
                            cout << "�Ѳ��w�Ȱ����!" << endl;
                            break;
                        }
                        else
                        {
                            flag = 1;
                            cout << "��J��X�q: ";
                            cin >> volume;
                            while(volume != (int)volume)//�P�_��J�O�_�����
                            {
                                cout<<"��J���~,�Э��s��J(���)"<<endl;
                                cin >> volume;
                            }
                            if(cust.share_holding_value[i] >= volume)
                            {
                                cust.share_holding_value[i] -= volume;
                                share[i].Free_Stocks_Float += volume;
                                cust.Balance += share[ i].Stock_Listed_Price*volume;
                                cust.Holding_Market_Value -= share[i].Stock_Listed_Price*volume;
                                system("cls");
                                cout << "������\!" << endl;
                                cout << endl;
                                ofstream data(cust.Customer_Name,ios::binary);
                                data.write((char*)(&cust),sizeof(cust));
                                Save(share);
                            }
                            else
                            {
                                cout << "�z�S�������Ѳ��i��X";
                                cout << "�αz�S���ʶR���Ѳ�" << endl;
                                cout << "�����N���^" << endl;
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
                            cout << "�z�S���ʶR�ӪѲ��αz��J���~" << endl;
                            cout << "�����N���^";
                            getch();
                            goto start;
                        }
                    }
                }
            }
            else
            {
                cout << endl << "��J���~!";
            }
            cin.get();
            break;
        }
        case '3'://��_�Ѳ����
        {
            if(cust.Administrator == 1)
            {
                system("cls");
                cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
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
                cout << "�z�L�v��_�Ѳ�!" << endl;
                getch();
                break;
            }
        }
        case '4'://����Ѳ�
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
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
                cout << "�z�L�v���_�Ѳ�!" << endl ;
                getch();
                break;
            }
        }
        case '5'://�ק�Ѳ�
        {
            if( cust.Administrator == 1 )
            {
                system("cls");
                cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
                cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
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
                cout << "�z�L�v������Ѳ�!" << endl;
                getch();
                break ;
            }
        }
        case '6'://�d�ݫH��
            system("cls");
            cout << "\t\t\t******************************�Ѳ��t��******************************" << endl;
            cout << "\t\t\t--------------------------------------------------------------------" << endl;
            cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
            for(int i=0; i<TOTALSTOCKS; i++)
            {
                cout << " "   << share[i].Stock_Name
                     << "\t\t" << share[i].Stock_Code
                     << "\t\t" << share[i].Stock_Volume
                     << "\t\t" << cust.share_holding_value[i]
                     << "\t\t" << share[i].Stock_Issue_Price
                     << "\t\t" << share[i].Stock_Listed_Price
                     << "\t\t" << (share[i].Close_Selling == 0?"������":"�w����") << endl;

            }
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " �����Ѳ�����\t\t�i�θ��\t�`�겣"<<endl;
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
    cout << "***************�Ѳ�����t��***************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "�i�J�Ѳ��������................[1]" << endl;
    cout << "�n���Τ�........................[2]" << endl;
    cout << "���U�s�Τ�......................[3]" << endl;
    cout << "�h�X���t��......................[0]" << endl;
    cout << endl << endl;
    cout << endl << "�п��:";
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
    case '0': //�N�h�X
    {
        system("cls");
        cout << "�P�¨ϥ�***************�Ѳ�����t��***************" << endl;
        cout << "\t���n�A��!!!!!!!!!!!!!!!" << endl;
        exit(0);
    }
    case '1': //�i�J�Ѳ��������
    {
        system("cls");
        cout << "\n\n\t\t***************�Ѳ��������**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        //cout << " ���q\t\t�N�X\t�y�q��\t�i�ʪ�\t�o���\t�W����\t���A" << endl;
        cout << " ���q�W��\t�N�X\t\t�y�q��\t\t�i�ʪ�\t\t\t�o���\t\t�W����\t\t���A" << endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share[i].Display_Stock_Market_Information();//��ܥ����H��
        }
        cin.get();
        getch();
        Interface(share);
        break;
    }
    case '2'://�n���Τ�
    {
        system("cls");
        cout << "\n\n\t\t***************�Ѳ��������**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        cout << "��J�b��:";
        cin >> cust.Customer_Name;
        cin.get();
        ifstream read_customer(cust.Customer_Name);//Ū�w���ƾ�//�n�A�ק�
        while( !read_customer.eof() )//�P�_�O�_���O��
        {
            read_customer.read((char*)(&cust),sizeof(cust));
            if( read_customer.fail() )
            {
                cout << endl;
                cout << "��Ʈw�S���O��" << endl;
                getch();
                Interface(share);
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
                    cust.Log_In(pass_word, share);
                    cin.get();
                    Interface(share);
                    break;
                }
                else
                {
                    cout << endl << "��J���~!";
                }
                read_customer.close();
                cin.get();
                break;
            }
        }
    }
    case '3':  //���U�s�Τ�
    {
        system("cls");
        cout << "���U�s�Τ�" << endl;
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

/*void Stock::Add_New_Stock()//�K�[�s�Ѳ�
{
    string name = "", code = "";
    system("cls");
    cin.get();
    cout << "��J�s�Ѳ��W(�r�ƭn����): ";
    cin >> name;

    while (name.size() > 20 || name.size() <= 0)
    {
        cout << "�Ѳ��W�������j��20�X�Φܤ֦�1�X" << endl;
        cout << "��J�z�n�ʶR���Ѳ��W��:";
        cin >> name;
    }
    cout << "��J�Ѳ��N�X(���ӥH��): ";
    cin >> code;
    while (code.size() > 5 || code.size() <= 0)
    {
        cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
        cout << "��J�z�n�ʶR���Ѳ��N�X:";
        cin >> code;
    }
    cout << "��J�y�q�Ѳ��ƶq: ";
    cin >> Stock_Volume;
    cout << "��J�Ѳ��o���: ";
    cin >> Stock_Issue_Price;
    cin.get();
    Free_Stocks_Float = Stock_Volume;
    Num_Of_Stock++;
    srand(time(NULL));//�H���ͦ��Ѳ��W����
    Stock_Listed_Price = (rand()%3+1)*Stock_Issue_Price + rand()%1000/10;//�üƽվ�
}*/

void Stock::Display_Stock_Market_Information()
{
    cout << " "   << Stock_Name
         << "\t\t" << Stock_Code
         << "\t\t" << Stock_Volume
         << "\t\t" << cust.share_holding_value
         << "\t\t" << Stock_Issue_Price
         << "\t\t" << Stock_Listed_Price
         << "\t\t" << (Close_Selling == 0?"������":"�w����") << endl;
}

/*void readFile()
{
    int update;//��s����
    double issuePrice, listedPrice, marketValue, opening, closing, current;//�o��� �W���� ���� �}�L ���L �R���
    string name, code;//�W�l �N�X
    long long floatNumber, shareVolume;// �Ѳ�����q �ۥѬy�q�ѥ�
    ifstream stockData;
    for (int i=0; i<TOTALSTOCKS; i++)
    {
        stockData.open("stockData" + enterprise[i] + ".txt");
        if (!stockData)
        {
            cout <<"Unable to open: "<< "stockData" << enterprise[i] << endl;
        }
        else {
            while (stockData >> name)//����Ū�J����Ū��̫�(�̷s)���@����
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
void Write_File()//�]�����ӹw�p�n����u�ϡA�ҥH��ios::app���C�@������s���i�H�Q�O���U��
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
    int update;//��s����
    double issuePrice, listedPrice, marketValue, opening, closing, current;//�o��� �W���� ���� �}�L ���L �R���
    string name, code;//�W�l �N�X
    long long floatNumber, shareVolume;// �Ѳ�����q �ۥѬy�q�ѥ�
    ifstream stockData;
    for (int i=0; i<TOTALSTOCKS; i++)
    {
        stockData.open("stockData" + STOCKNAME[i] + ".txt");
        if (!stockData)
        {
            cout <<"Unable to open: "<< "stockData" << STOCKNAME[i] << endl;
        }
        else {
            while (stockData >> name)//����Ū�J����Ū��̫�(�̷s)���@����
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
        cout << "�Ѳ��W��/�N�X" << " �Ѳ��o��� �Ѳ��W���� ���� �y�q�ѥ��q ����q �}�L�� ���L�� �ثe�R�����" << endl;
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
    cout << "�п�J�ﶵ���X" << endl;
    cout << "---------------------------" << endl;
    cout << "1.��ܩҦ��Ѳ���T" << endl;
    cout << "2.��ܯS�w�Ѳ���T" << endl;
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
void Stock::Close_Selling_Stock(vector <Stock> share)//�Ȱ��Ѳ����
{
    char input;
    string share_code = "";
    cout<<"��J�z�n���骺�Ѳ��N�X:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
        cout << "��J�z�n�ʶR���Ѳ��N�X:";
        cin >> share_code;
    }
    int i=0;
    flag = 0;
    if( share_code != "")//���J�^���ɳ���
    {
        while( (i<TOTALSTOCKS) && (!flag) )
        {
            if(share[i].Stock_Code == share_code)
            {
                flag = 1;
                cout << "�T�w(y/n)";
                cin >> input;
                if(input == 'y')
                {
                    share[i].Close_Selling = 1;
                    Save(share);
                    cout << "�w����" << endl;
                    cout << endl;
                    break;
                }
                else if(input=='n')
                {
                    cout << "�B������!" << endl;
                }
                else
                {
                    cout << "��J���~!" <<endl;
                }
            }
            else i++;
            if(i == TOTALSTOCKS)
            {
                cout << "�z��J���N�X���~!" << endl;
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
    cout << "��J�z�n��_������Ѳ��N�X:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
        cout << "��J�z�n��_������Ѳ��N�X:";
        cin >> share_code;
    }
    int i= 0;
    flag = 0;
    while( (!flag) && (i<TOTALSTOCKS) )
    {
        if( share[i].Stock_Code == share_code )
        {
            flag = 1;
            cout << "�T�w(y/n)";
            cin >> input;
            if(input == 'y')
            {
                share[i].Close_Selling = 0;
                Save(share);
                cout << "�w��_" << endl;
                cout << endl;
                break;
            }
            else if(input == 'n')
            {
                cout << "�B�J����!" << endl;
            }
            else
            {
                cout << "��J���~!" <<endl;
            }
        }
        else i++;
        if(i == TOTALSTOCKS)
        {
            cout << "�z��J���N�X���~!" << endl;
            break;
        }
    }
    getch();
}

/*void Stock::Delete_Stock()//�R���Ѳ�
{
    char input,share_code[6];
    cout << "��J�R���Ѳ��N�X:";
    cin.getline(share_code,6);
    int i= 0;
    flag = 0;
    if( strcmp(share_code,"") != 0 )//���J�^���ɳ���
    {
        while( (i<TOTALSTOCKS) && (!flag) )
        {
            if( strcmp(share[i].Stock_Code,share_code) == 0 )
            {
                flag = 1;
                cout << "�T�w(y/n)";
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
                    cout << "�B�J����!" << endl;
                }
                else
                {
                    cout << "��J���~!" << endl;
                }
            }
            else i++;
            while(i == TOTALSTOCKS)
            {
                cout << "�z��J���N�X���~!" << endl;
                break;
            }
        }
    }
    else
    {
        cout<<"��J���~!";
    }
}*/

void Stock::Modify_Stock(vector <Stock> t)//�վ��T
{
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "��J�줽�q�N�X" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
        cout << "��J�z�n��_������Ѳ��N�X:";
        cin >> share_code;
    }
    if( share_code != "" )//���J�^����ɳ���
    {
        while( (i < TOTALSTOCKS) && (!flag) )
        {
            if (t[i].Stock_Code == share_code)
            {
                if(t[i].Close_Selling == 1)
                {
                    cout<<"�Ȱ��Ѳ����!"<<endl;
                    break;
                }
                else
                {
                    cin.clear();
                    flag = 1;
                    cout << "��J�s�ѦW(�ѤF�h�֥H��):" << endl;
                    cin >> share_name;
                    while (share_name.size() > 20 || share_name.size() <= 0)
                    {
                        cout << "�Ѳ��W�������j��20�X�Φܤ֦�1�X" << endl;
                        cout << "��J�z�n�ʶR���Ѳ��W��:";
                        cin >> share_name;
                    }
                    t[i].Stock_Name = share_name;
                    cin.get();
                    cout << "��J�s�N�X(5�H��)";
                    cout << endl;
                    cin >> share_code;
                    while (share_code.size() > 5 || share_code.size() <= 0)
                    {
                        cout << "�Ѳ��N�X�����j��5�X�Φܤ֦�1�X" << endl;
                        cout << "��J�z�n��_������Ѳ��N�X:";
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
                cout << "�Ѳ����s�b!" << endl;
                cout << "�����N���^..." << endl;
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

void Stock::randomChange(vector <Stock> share)
{
    int i = 0;
    int lastTime = 0;
    while (1) {
        int now = getTime();
        /*------ �C�L30��B��--------*/
        if (now - lastTime > 30) {
            for(int j=0; j<share.size(); j++) {
                double amount_of_increase = Random(); //�B�ʦʤ���

                if(amount_of_increase == 0) {        //��������
                    share[i].color = 0;
                }
                else if(amount_of_increase > 0) {       //�W��

                    share[i].Stock_Listed_Price *= (1 + amount_of_increase);

                    if(amount_of_increase == 0.1) {     //���T�F10%
                        share[i].color = 2;
                        share[i].Close_Selling = 1;
                    }
                    else {                              //���T�p��10%
                       share[i].color = 2;
                       share[i].Stock_Listed_Price *= (1 + amount_of_increase);
                    }
                }
                else if(amount_of_increase < 0) {        //�U�^

                    share[i].Stock_Listed_Price *= (1 + amount_of_increase);

                    if(amount_of_increase == -0.1) {    //�U�^�F10%
                        share[i].color = 1;
                        share[i].Close_Selling = 1;
                    }
                    else {                               //�U�^�p��10%
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
    int x = rand() % (Max - Min + 1) + Min; // x���d��[-10, 10]
    return x*0.01; //���ʤ���
}

int main()
{
    ifstream dataFile("Stock_File.txt"); //Ū���Ѳ��ƾ�
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
    thread t1(&Stock::randomChange, &temp, share);  //�h����ǡA����Ѳ��B��
    t1.detach();
    Interface(share);
}
