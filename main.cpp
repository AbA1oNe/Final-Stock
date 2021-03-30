class Stock
{
private:

    float Stock_Issue_Price:
    float Stock_Listed_Price;
    string Stock_Name;
    long long Stock_Code[index];
    bool Hang;
    long long Number_Of_Listed_Stocks;
    long long Free_Stocks_Float;
    long long The_Share_Volume_Of_Stocks

public:

    void Add_New_Stock();
    void Delete_Stock();
    void Modify_Stock();
    void Menu();
    void Display_Stock_Market_Information();
    /*display infomation®§
    (
    1.Opening Price
    2.losing Price
    3.Limit Up
    4.Limit Down
    5.Bid Price
    6.Ask Price / Offer Price
    ......
    )
    */
    void Hang_Up_Stock();
    void Un_Hang_Stock();
    void Write_File();

};

class Customer
{
private:
    string Customer_Name[elements];
    string Customer_Password[elements];
    long long Holding_Stock_Numbers[elements];
    string Holding_Stock_Name[elements];
    long long Holding_Stock_code[elements];
    double Balance;
    double Market_Value;­È
    double Total_Assets;
    bool Administrator;

public:

    void Log_In();
    void Register();¥U

};
