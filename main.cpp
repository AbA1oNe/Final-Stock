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

const int TOTALSTOCKS = 10;//�]�w����X�ӪѲ������
int flag;
double Random();    //�B�ʪѲ���Function
int main();

class Customer;

class Stock
{
    friend class Customer;
private:
    unsigned long long Stock_Volume;    //�Ѳ��`�Ѽ�   //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    unsigned long long Free_Stocks_Float;//�ۥѬy�q�ѥ� //10�쥿��� //0 �� 4,294,967,295 //1�i1000��
    long long int The_Share_Volume_Of_Stocks;//???????q //????
    string Stock_Name;            //�Ѳ��W��
    string Stock_Code;             //�Ѳ��N�X
    double Stock_Issue_Price;       //�Ѳ��o���
    double Stock_Listed_Price;      //�Ѳ��W����
    double Market_Value;            //�Ѳ�����
    double openingPrice;            //�}�L�� 
    double closingPrice;            //���L��       //����
    double currentPrice;            //�R���
    bool Close_Selling;             //�O�_�Ȱ�����Ҩ�]1���O�A0���_�^//�쥻�i�H�Ĩ骺�Ѳ��A�Ȯɤ���A�H�Ĩ��X�C//Short_Selling_Suspended
    int color;                      //�C��
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
    string Customer_Name;//?�V?W
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
Customer cust;//?n???�V??H?A??????q


void Customer::Log_In(string pass_word, vector <Stock> share, time_t startTime) const//?n??
{
    if( pass_word == Customer_Password )//???K?X
    {
        Stock_Portfolio(share, startTime);
    }
    else
    {
        cout << endl;
        cout << "�K�X���~"<<endl;
    }
}

void Customer::Register(Customer *cust)//???U?b??
{
    char input;
    system("cls"); //????t?�[R?O?G?M??=cls
    cin.get();
    cout << "�w��i�J---------------�Ѳ��t��---------------" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "�п�J�b��/�Τ�W: ";
    cin >> Customer_Name;
    cout << "�п�J�K�X(�֩�8 �r): " << endl;
    cin >> Customer_Password;
    while (Customer_Password.size() <= 0 || Customer_Password.size() > 8)
    {
        cout << "�K�X����j��8�Ӧr���Φܤ֭n���@�Ӧr��" << endl;
        cout << "�п�J�K�X(�֩�8 �r): " << endl;
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

void Customer::Stock_Portfolio(vector <Stock> share, time_t startTime) const//?�V?????@?????t??
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
    cout << "\t\t �ק�Ѳ��N�X�ΦW��............[5]" << endl;//?i?H?A?s?W?n???
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
            cout << "\t\t\t------------------------------�Ѳ��t��------------------------------" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
            for(int i=0; i < TOTALSTOCKS; i++)
            {
                share[i].Display_Stock_Market_Information();//???????H??
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
                cout << "�Ѳ��N�X�ݤp��5�X�Φܤ֦��@�X" << endl;
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
                            Max_Buy_Stock_Volume = int(cust.Balance/share[i].Stock_Listed_Price);//????
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
            cout << endl << "��J��X�Ѳ��N�X: ";
            code = "";
            while (code.size() > 5 || code.size() <= 0)
            {
                cout << "�Ѳ��N�X���p��5�X�Φܤ֦��@�X" << endl;
                cout << "��J��X�Ѳ��N�X: ";
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
                            while(volume != (int)volume)//?P?_??J?O?_?????
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
        case '4'://??????
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
                cout << "�z�L�v���ק�Ѳ�!" << endl;
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

void Interface(vector <Stock> share, time_t startTime)
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
    case '0': //�N�h�X
    {
        system("cls");
        cout << "�P�¨ϥ�***************�Ѳ�����t��***************" << endl;
        cout << "\t���n�A��!!!!!!!!!!!!!!!" << endl;
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
                double x = rand() % 21 -10; // x???d??[-10, 10]
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
        cout << "\n\n\t\t***************�Ѳ��������**************" << endl;
        cout << "\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~" << endl;
        cout << " ���q�W��\t\t�N�X\t�y�q��\t\t�i�ʪ�\t\t�o���\t\t�W����\t\t���A" << endl;
        for(int i=0; i < TOTALSTOCKS; i++)
        {
            share[i].Display_Stock_Market_Information();//��ܥ����H��
        }
        cin.get();
        getch();
        main();
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
         << "\t\t" << (Close_Selling == 0?"������":"�w����") << endl;
}

void Stock::Close_Selling_Stock(vector <Stock> share)//�Ȱ��Ѳ����
{
    char input;
    string share_code = "";
    cout<<"��J�z�n���骺�Ѳ��N�X:";
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "�Ѳ��N�X�ݤp��5�Φܤ֦��@�X" << endl;
        cout << "��J�z�n���骺�Ѳ��N�X:";
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
        cout << "�Ѳ��N�X�ݤp��5�X�Φܤ֤j��@�X" << endl;
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

void Stock::Modify_Stock(vector <Stock> t)//�վ��T
{
    flag = 0;
    int i=0;
    string share_name = "", share_code = "";
    cin.clear();
    cout << "��J�줽�q�N�X:" << endl;
    cin >> share_code;
    while (share_code.size() > 5 || share_code.size() <= 0)
    {
        cout << "�Ѳ��N�X�ݤp��5�X�Φܤ֦��@�X" << endl;
        cout << "��J�줽�q�N�X:";
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
                    cout<<"�Ȱ��Ѳ����!"<<endl;
                    break;
                }
                else
                {
                    cin.clear();
                    flag = 1;
                    cout << "��J�s�ѦW(20�r���H��):" << endl;
                    cin >> share_name;
                    while (share_name.size() > 20 || share_name.size() <= 0)
                    {
                        cout << "�Ѳ��W�ٻݤp��20�r���Τj��@�r��" << endl;
                        cout << "��J�s�ѦW(20�r���H��):";
                        cin >> share_name;
                    }
                    t[i].Stock_Name = share_name;
                    cin.get();
                    cout << "��J�s�Ѳ��N�X(5�X�H��):";
                    cout << endl;
                    cin >> share_code;
                    while (share_code.size() > 5 || share_code.size() <= 0)
                    {
                        cout << "�Ѳ��N�X�ݤp��5�X�Τj��@�X" << endl;
                        cout << "��J�s�Ѳ��N�X(5�X�H��):";
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
