class Stock
{
private:

    float Stock_Issue_Price://�Ѳ��o���
    float Stock_Listed_Price;//�Ѳ��W����
    char Stock_Name[index];//�Ѳ��W��
    char Stock_Code[index];//�Ѳ��N�X
    bool Hang;//�O�_���_
    long long int Number_Of_Listed_Stocks;//�W���Ѳ���
    long long int Free_Stocks_Float;//�ۥѬy�q�ѥ�
    long long int The_Share_Volume_Of_Stocks//�Ѳ�����q

public:

    void Add_New_Stock();//�[�J�s�Ѳ�
    void Delete_Stock();//�R���Ѳ�
    void Modify_Stock();//�ק�Ѳ����
    void Menu();//��ܵ��
    void Display_Stock_Market_Information();
    /*�i�ܦU���ѥ��H��
    (
    1.�}�L���GOpening Price
    2.���L���GClosing Price
    3.�����GLimit Up
    4.�^���GLimit Down
    5.�R���GBid Price
    6.����GAsk Price / Offer Price
    ......��
    )
    */
    void Hang_Up_Stock();//���_�Ѳ�
    void Un_Hang_Stock();//�ѱ��Ѳ�
    void Write_File();//�g��(�C�����槹�s��)

};

class Customer
{
private:
    string Customer_Name[elements];//�Τ�W
    string Customer_Password[elements];//�K�X
    long long int Holding_Stock_Numbers[elements];//�����Ѳ��ƶq
    char Holding_Stock_Name[elements][elements];//�����Ѳ��W��
    char Holding_Stock_code[elements][elements];//�����Ѳ��N�X
    double Balance;//�{���l�B
    double Market_Value;//����
    double Total_Assets;//�`�겣
    bool Administrator;//�O�_���޲z��

public:

    void Log_In();//�n��
    void Register();//���U

};
