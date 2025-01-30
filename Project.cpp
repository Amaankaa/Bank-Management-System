#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>

using namespace std;

struct account
{
    int acno;
    char name[50];
    int deposit;
    char type;
};

void write_account();
void display_all();
void display_sp(int);
void delete_account(int);
void deposit_withdraw(int, int);
void intro();

account ac;

int main()
{
    system("color 1B");
    char choice;
    int num;
    intro();
    system("cls");

    cout<<"*****Welcome to our Bank*****\n";

    cout<<"==============================\n";
    cout<<"         MAIN MENU           \n";
    cout<<"==============================\n\n";

    do
    {
        cout<<"1. Create an account \n";
        cout<<"2. Deposit Money \n";
        cout<<"3. Withdraw Money \n";
        cout<<"4. Balance Enquiry \n";
        cout<<"5. Display Existing Accounts \n";
        cout<<"6. Delete an Account\n";
        cout<<"7. Exit \n";

        cout<<"Enter your choice: ";
        cin>>choice;
        system("cls");
        cin.clear();
        fflush(stdin);
        switch(choice)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n\nEnter the account PIN: "; cin>>num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout<<"\n\nEnter the account PIN: "; cin>>num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout<<"\n\nEnter the account PIN: "; cin>>num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"\n\nEnter the account PIN: "; cin>>num;
            delete_account(num);
            break;
        case '7':
            cout<<"\n\nThank you for banking with us!\n";
            break;
        default:
            cout<<"\n\n\a\a\aInvalid Input\n\n";
        }
        system("pause");
    }while(choice!='7');
}
void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary|ios::app);
    cout<<"\nEnter The Account PIN: ";
    cin>>ac.acno;
    cout<<"\nEnter your name: ";
    cin.ignore();
    cin.getline(ac.name, 50);
    cout<<"\nEnter the account type (C/S): ";
    cin>>ac.type;
    ac.type = toupper(ac.type);
    cout<<"\nEnter Initially deposited amount: $";
    cin>>ac.deposit;
    cout<<"\n\nAccount created successfully!\n\n";
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File not found!...\n";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *> (&ac) , sizeof(account));
        if (ac.acno==n)
        {
            cout << "\nAccount No. : " << ac.acno
                 << "\nAccount Holder Name: " << ac.name
                 << "\nAccount Type: " << ac.type
                 << "\nRemaining Amount: " << ac.deposit
                 <<endl << endl;

                 if(option == 1)
                 {
                     cout<<"\n\nEnter amount to be deposited: $";
                     cin>>amt;
                     ac.deposit+=amt;
                 }
                 if(option==2)
                 {
                     cout<<"\nEnter amount to be withdrawn: $";
                     cin>>amt;
                     int bal = ac.deposit-amt;
                     if((bal<500 && ac.type == 'S') || (bal<1000 && ac.type=='C'))
                        cout<<"Your balance is insufficient!\n";
                     else
                        ac.deposit-=amt;
                 }
                 int pos=(-1)*static_cast<int>(sizeof(ac));
                 File.seekp(pos, ios::cur);
                 File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                 cout<<"\n\n\t Record Updated\n";
                 found = true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";

}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary|ios::in);
    if(!inFile)
    {
        cout<<"\nFile not found!\n";
        return;
    }
    cout<<"\nBalance Details\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.acno==n)
        {
            cout<<"\nAccount No. : "<<ac.acno
                <<"\nAccount Holder Name: "<<ac.name
                <<"\nType of account: "<<ac.type
                <<"\nBalance Amount: $"<<ac.deposit<<endl;
                flag = true;
        }
    }
    inFile.close();
    if(flag == false)
        cout<<"\n\nAccount number does not exist!";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"\nFile not found\n";
        return;
    }
    cout<<"\n\nACCOUNT HOLDER LIST \n\n"
        <<"=====================================================================\n"
        <<setw(20) << setiosflags(ios::left)
        <<"Account No." << setw(25)
        << "NAME" << setw(15)
        << "Type" << setw(10) << "Balance" << setw(10)
        <<"\n=====================================================================\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            cout<<setw(20) << setiosflags(ios::left)
                <<ac.acno << setw(25)
                <<ac.name << setw(15)
                <<ac.type << "$"
                <<ac.deposit << setw(10) <<endl;
        }
        inFile.close();
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File not found\n\n";
        return;
    }
    outFile.open("Temped1.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.acno!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temped1.dat", "account.dat");
    cout<<"\n\nRecord Updated .. ";
}

void intro()
{
    cout << "\t\t\t*************************************\n"
         << "\t\t\t*             C++ PROJECT           *\n"
         << "\t\t\t*                                   *\n"
         << "\t\t\t*       BANK MANAGEMENT SYSTEM      *\n"
         << "\t\t\t*                                   *\n"
         << "\t\t\t*STUDENTS NAME          STUDENTS ID *\n"
         << "\t\t\t*===================================*\n"
         << "\t\t\t*1.Amanuel Merara       UGR/30138/15*\n"
         << "\t\t\t*2.Abenezer Gdilew      UGR/30076/15*\n"
         << "\t\t\t*3.Yosef Solomon        UGR/31454/15*\n"
         << "\t\t\t*4.Mikiyas Abebe        UGR/26684/15*\n"
         << "\t\t\t*5.Lemi Abduljebar      UGR/30821/15*\n"
         << "\t\t\t*************************************\n"
         << endl;

    cout<<"\nEnter any key to contine\n";
    cin.get();
}
