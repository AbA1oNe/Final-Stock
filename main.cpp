#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
//�Ѳ���s�hupdateTimes++,�åB�g�ɦA���sŪ��

using namespace std;

const int TOTALSTOCKS = 10;//�]�w����X�ӪѲ������
const string STOCKNAME[TOTALSTOCKS] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};//TOTALSTOCKS�ӪѲ���ƪ�txt�ɮ�

class Stock
{
private:
    string Stock_Name;//�Ѳ��W��
    string Stock_Code;//�Ѳ��N�X
    int updateTimes;//��s����, ���ӧ�u�Ϩϥ�
    double Stock_Issue_Price;//�Ѳ��o���
    double Stock_Listed_Price;//�Ѳ��W����
    double Market_Value;//����
    long long int Free_Stocks_Float;//�ۥѬy�q�ѥ�
    long long int The_Share_Volume_Of_Stocks;//�Ѳ�����q
    double openingPrice;//�}�L��
    double closingPrice;//���L��
    double currentPrice;//�R���

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
    void Add_New_Stock();//�[�J�s�Ѳ�(�޲z��)
    void Delete_Stock();//�R���Ѳ�(�޲z��)
    void Modify_Stock();//�ק�Ѳ����(�޲z��)
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
    friend void Write_File();//�g��
                            //�H�U����private data
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

    bool checkFloat();//�ˬd�B�� �p�G���htrue
    double randomChange();//�H�ɶ����ܥثe������

}Enterprise[TOTALSTOCKS];

void Stock::setEverything(string name, string code, int update, double issue, double listed, double market, long long floatStock, long long shareVolume, long long opening, long long closing, long long current)
{   //�]�wclass��private data
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
    string Customer_Name;//�Τ�W
    string Customer_Password;//�K�X
    struct holdingStock
    {
        long long holdingNumbers;//�����Ѳ��ƶq
        string Holding_Stock_Name;//�����Ѳ��W��
        string Holding_Stock_code;//�����Ѳ��N�X
        double StockPrice;//�ӪѲ��R�i������
    };
    double Balance;//�{���l�B
    double Total_Assets;//�`�겣
    bool Administrator;//�O�_���޲z��

public:
    void Log_In();//�n��
    void Register();//���U
    void buy();//�R
    void sell();//��
    string getName();
    string getPass();
    holdingStock getHoldingStock();
    double getBalance();
    double getTotalAsset();
    bool getAdmin();
};

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


int main()
{
    readFile();
    menu();
}
