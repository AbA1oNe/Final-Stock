class Stock
{
private:

    float Stock_Issue_Price://布祇︽基
    float Stock_Listed_Price;//布カ基
    char Stock_Name[index];//布嘿
    char Stock_Code[index];//布絏
    bool Hang;//琌本癬
    long long int Number_Of_Listed_Stocks;//カ布计
    long long int Free_Stocks_Float;//パ瑈硄
    long long int The_Share_Volume_Of_Stocks//布Θユ秖

public:

    void Add_New_Stock();//穝布
    void Delete_Stock();//埃布
    void Modify_Stock();//э布戈
    void Menu();//匡拒垫虫
    void Display_Stock_Market_Information();
    /*甶ボ兜カ獺
    (
    1.秨絃基Opening Price
    2.Μ絃基Closing Price
    3.害氨Limit Up
    4.禴氨Limit Down
    5.禦基Bid Price
    6.芥基Ask Price / Offer Price
    ......单
    )
    */
    void Hang_Up_Stock();//本癬布
    void Un_Hang_Stock();//秆本布
    void Write_File();//糶郎(–Ω磅︽Ч郎)

};

class Customer
{
private:
    string Customer_Name[elements];//ノめ
    string Customer_Password[elements];//盞絏
    long long int Holding_Stock_Numbers[elements];//Τ布计秖
    char Holding_Stock_Name[elements][elements];//Τ布嘿
    char Holding_Stock_code[elements][elements];//Τ布絏
    double Balance;//瞷緇肂
    double Market_Value;//カ
    double Total_Assets;//羆戈玻
    bool Administrator;//琌恨瞶

public:

    void Log_In();//祅魁
    void Register();//爹

};
