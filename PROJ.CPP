

#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account();
	void modify();
	void dep(int);
	void draw(int);
	void report();
	int retacno();
	int retdeposit();
	char rettype();
};

void account::create_account()
{
	cout<<"\nEnter The account No.";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nThe account No."<<acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The amount : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\t\t\t\t\tMAIN MENU";
		cout<<"\n\n\t\t\t01. NEW ACCOUNT";
		cout<<"\n\n\t\t\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t\t\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t\t\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t\t\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t\t\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t\t\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t\t\t08. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-8) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\t\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\t\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\t\t\t\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\t\t\t\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\t\t\t\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\n\n\n\n\n\n\n\t\t   Thanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		getch();
	}while(ch!='8');
	return 0;
}
 void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\t\t\tBALANCE DETAILS\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n\t\t\t\tAccount number does not exist";
}
void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\t\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t\t\t\t\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\t\tTO DEPOSITE AMOUNT ";
				cout<<"\n\n\t\t\t\tEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\t\t\t\tTO WITHDRAW AMOUNT ";
				cout<<"\n\n\t\t\t\tEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}
void intro()
{
	cout<<"\n\n\n\t\t\t\t  BANK";
	cout<<"\n\n\t\t\t\tMANAGEMENT";
	cout<<"\n\n\t\t\t\t  SYSTEM";
	cout<<"\n\n\n\n\t\tMADE BY : MANPREET RATHORE";
	getch();
}
