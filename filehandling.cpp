#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<math.h>

using namespace std;
void Input();
void UpdateRate();
void Issuing();
void StockDisplay();
int SearchItemCode(int);
void UpdateItem(int);
void DeleteItem(int);
void UpdateQuantity(int,int);
class Item
{
private :
    int Item_Code;
    char Item_Name[20];
    int Item_Quantity;
    float Item_Rate;
public:
    Item()
    {}
    Item(int Item_Code,char Item_Name[20], int Item_Quantity, float Item_Rate)
    {
        this->Item_Code = Item_Code;
        strcpy(this->Item_Name, Item_Name);
        this->Item_Rate = Item_Rate;
        this->Item_Quantity= Item_Quantity;
    }
    Item(Item &I)
    {
        Item_Code=I.Item_Code;
        Item_Quantity=I.Item_Quantity;
        Item_Rate=I.Item_Rate;
        strcpy(Item_Name,I.Item_Name);
    }
    void setItemData()
    {
        InputName();
        InputQuantity();
        InputRate();
    }
    void Display()
    {
        cout<<endl<<Item_Code<<endl<<Item_Name<<endl<<Item_Quantity<<endl<<Item_Rate;
    }
    void setCode(int Code)
    {
        Item_Code=Code;
    }
    void setQuantity(int Quantity)
    {
        Item_Quantity=Quantity;
    }
    void setRate(float Rate)
    {
        Item_Rate=Rate;
    }

    void setName(char Name[20])
    {
        strcpy(Item_Name,Name);
    }
    void InputCode()
    {
        int Code;
        cout<<"\nEnter the Item_Code :  ";
        cin>>Code;
        Item_Code= Code;
    }
    void InputName()
    {
        char Name[20];
        cout<<"\nEnter the Item_Name :  ";
        fflush(stdin);
        cin>>Item_Name;
    }
    void InputQuantity()
    {
        int Quantity;
        cout<<"\nEnter the Item_Quantity :  ";
        cin>>Quantity;
        Item_Quantity= Quantity;
    }
    void InputRate()
    {
        float Rate;
        cout<<"\nEnter the Item_Rate : ";
        cin>>Rate;
        Item_Rate= Rate;
    }
    float getRate()
    {
        return Item_Rate;
    }
    int getQuantity()
    {
        return Item_Quantity;
    }
    char* getName()
    {
        return Item_Name;
    }
    int getCode()
    {
        return Item_Code;
    }
    void setItem(Item I)
    {
        this->setCode(I.Item_Code);
        this->setName(I.Item_Name);
        this->setRate(I.Item_Rate);
        this->setQuantity(I.Item_Quantity);
    }
    void ShowOneData()
    {
        cout<<"\nItem Code : "<<Item_Code<<"\tItem Name : "<<Item_Name<<"\tItem Quantity : "<<Item_Quantity<<"\tItem Rate : "<<Item_Rate;
    }
    void ShowData()
    {
        cout<<"\n"<<Item_Code<<"\t\t"<<Item_Name<<"\t\t"<<Item_Quantity<<"\t\t"<<Item_Rate;
    }
};
void Input()
{
    fflush(stdin);
    ofstream dout;
    int Code;
    dout.open("Stock.txt",ios::app| ios::binary);
    Item I;
    cout<<endl<<"Enter Code :: ";
    cin>>Code;
    I.setCode(Code);
    if(SearchItemCode(Code)==1)
    {
        UpdateItem(Code);
    }
   else
    {
        I.setItemData();
        dout.write((char*)&I,sizeof(I));
    }

    dout.close();
}
void UpdateItem(int Code)
{
    fstream file;
    int newStock;
    file.open("Stock.txt",ios::in|ios::binary|ios::out|ios::ate);
    Item I;
    file.seekg(0);
    file.read((char*)&I,sizeof(I));
    while(!file.eof())
    {
        if(I.getCode()==Code)
        {
            I.ShowOneData();
            cout<<"\nEnter the quantity arrived in the Stock :  ";
            cin>>newStock;
            newStock = newStock+I.getQuantity();
            I.setQuantity(newStock);
            file.seekp(file.tellp()-sizeof(I));
            file.write((char*)&I,sizeof(I));
        }
        file.read((char*)&I,sizeof(I));
    }
    file.close();
}
void UpdateQuantity(int Quantity, int Code)
{
    fstream file;
    file.open("Stock.txt",ios::in|ios::binary|ios::out|ios::ate);
    Item I;
    file.seekg(0);
    file.read((char*)&I,sizeof(I));
    while(!file.eof())
    {
        if(I.getCode()==Code)
        {
            I.setQuantity(Quantity);
            file.seekp(file.tellp()-sizeof(I));
            file.write((char*)&I,sizeof(I));
        }
        file.read((char*)&I,sizeof(I));
    }
    file.close();
}
void UpdateRate()
{
    fstream file;
    int Code;
    float rate;
    file.open("Stock.txt",ios::in|ios::binary|ios::out|ios::ate);
    Item I;
    file.seekg(0);
    file.read((char*)&I,sizeof(I));
    cout<<"\nEnter the Item Code: ";
    cin>>Code;
    if(SearchItemCode(Code)==0)
    {
        cout<<"\nItem is not in the Stock";
        return;
    }
    while(!file.eof())
    {
        if(I.getCode()==Code)
        {
            I.ShowOneData();
            cout<<"\nEnter New Rate :  ";
            cin>>rate;
            I.setRate(rate);
            file.seekp(file.tellp()-sizeof(I));
            file.write((char*)&I,sizeof(I));
        }
        file.read((char*)&I,sizeof(I));
    }
    file.close();
}
void Issuing()
{
    int Code;
    int Quantity;
    cout<<"\nEnter the Item Code : ";
    cin>>Code;
    Item I;

   if(SearchItemCode(Code))
   {
        ifstream din;
        din.open("Stock.txt",ios::in|ios::binary);
        din.read((char*)&I,sizeof(I));
        while(!din.eof())
        {
            if(I.getCode()==Code)
                break;
            din.read((char*)&I,sizeof(I));
        }
        din.close();
        I.ShowOneData();
        cout<<"\nEnter the Quantity : ";
        cin>>Quantity;
        if(Quantity>I.getQuantity())
           cout<<"\nItem cannot be dispatched.\n No of items Available : "<<I.getQuantity();
        else
        {
            if(Quantity == I.getQuantity())
            {
                DeleteItem(Code);
                return;
            }
            else
                UpdateQuantity(I.getQuantity()-Quantity,Code);
        }
   }
   else
   {
       cout<<"\nItem is not available in the stock";
   }

}
void StockDisplay()
{

    Item I;
    ifstream din;
    din.open("Stock.txt",ios::in|ios::binary);
    if(!din)
    {
        cout<<"\nEmpty Stock";
        return;
    }
    if(din.eof())
    {
        cout<<"\nEmpty Stock";
        return;
    }
    else
    {
        cout<<"\nItem Code\tItem Name\tItem Quantity\tItem Rate";
        din.read((char*)&I,sizeof(I));
        while(!din.eof())
        {
            I.ShowData();
            din.read((char*)&I,sizeof(I));
        }
    }
    din.close();
}
int SearchItemCode(int code)
{
    Item I;
    ifstream din;
    din.open("Stock.txt",ios::in|ios::binary);
    din.read((char*)&I,sizeof(I));
    while(!din.eof())
    {
        if(I.getCode()==code)
            return 1;
        din.read((char*)&I,sizeof(I));
    }
    return 0;
}
void DeleteItem(int Code)
{
    ifstream din;
    ofstream dout;
    Item I;
    din.open("Stock.txt",ios::in|ios::binary);
    if((!din))
    {
        cout<<"\nEmpty Stock";
        return;
    }
    if(din.eof())
    {
        cout<<"\nEmpty Stock";
        return;
    }
    else
    {
        dout.open("TempStock.txt",ios::out|ios::binary);
        din.read((char*)&I,sizeof(I));
        while(!din.eof())
        {
            if(!(I.getCode()== Code))
            {
                dout.write((char*)&I,sizeof(I));
            }
            din.read((char*)&I,sizeof(I));
        }
        din.close();
        dout.close();
        remove("Stock.txt");
        rename("TempStock.txt","Stock.txt");
    }
}
int main()
{
    int choice;
    system("title Stock List");
    system("cls");
    cout<<"\t\t\t\t\tWelcome to Stock Market"<<endl;
    while(1)
    {
        cout<<"\nSelect the Choice form the following."<<endl;
        cout<<"\n1.Insertion of items.\n2.Update the rate\n3.Issuing of item\n4.Stock List\n5.Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1 :
            Input();
            fflush(stdin);
            break;
        case 2 :
            UpdateRate();
            break;
        case 3 :
            Issuing();
            break;
        case 4 :
            StockDisplay();
            break;
        case 5:
             exit(0);
             break;
        default:
            cout<<endl<<"\nWrong Choice Selected"<<endl;
        }
    }
    getch();

    return 0;
}
