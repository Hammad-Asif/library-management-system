#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
using namespace std;
void list();
void listissued();
int fileSizestu();
struct student{
	string id,name,phnNo,bookId;
};
struct Book{
	string name,stock,price,id;
};
void removeByBook(string idcheck)
{
	int totalstu=fileSizestu(),u=0;
	student b[totalstu],c[totalstu-1];
	fstream stu;
	stu.open("students.txt",ios::in);
	if(stu)
	{
		int i=0;
		u=0;
		while(i<totalstu)
		{
			stu>>b[i].id>>b[i].name>>b[i].bookId>>b[i].phnNo;
			if(b[i].bookId!=idcheck)
			{
				c[u]=b[i];
				u++;
			}
				i++;
		}
		stu.close();
	}
	
	stu.open("students.txt",ios::out);
	if(stu)
	{
		int j=0;
		while(j<(sizeof(c)/sizeof(*c)))
		{
		stu<<c[j].id<<"\t"<<c[j].name<<"\t"<<c[j].bookId<<"\t"<<c[j].phnNo<<"\n";
		j++;
		}
	
	}
	stu.close();

}
void login()
{
	us:
	cout<<"\t\t\tLog In Panel"<<endl;
	string name="",pass="";
	cout<<"Enter User Name: ";
	cin>>name;
	if(name=="lab")
	{
		int passcount=1;
		pa:
		if(passcount<=3)
		{
			system("cls");
			cout<<"\t\t\tLog In Panel"<<endl;
			cout<<"User Name: "<<name<<endl;
			cout<<"Enter Password: ";
			cin>>pass;
			if(pass!="ros123")
			{
				cout<<"\n\n\tInvalid Password";
				getch();
				passcount++;
				goto pa;
			}
		}
		else
		{
			cout<<"\n\n\tPassword Try Over.";
			exit(0);
		}
	}
	else
	{
		cout<<"\n\nWrong User Name..";
		goto us;
	}
}
void add()
{
	Book b;
	cout<<"Enter Book id: ";
	cin>>b.id;
	cout<<"Enter Book name: ";
	cin>>b.name;
	cout<<"Enter Book stock: ";
	cin>>b.stock;
	cout<<"Enter Book Price: ";
	cin>>b.price;
	fstream book;
	book.open("Books.txt",ios::in|ios::out|ios::app);
	if(book)
	{
		book<<"\n"<<b.id<<"\t"<<b.name<<"\t"<<b.stock<<"\t"<<b.price;
	}
	book.close();
	string file=b.id+".txt";
	book.open(file.c_str(),ios::in|ios::out|ios::app);
	if(book)
	{
		book<<b.stock;
	}
	cout<<"New Book has been added";
	getch();
}
int fileSizeBook()
{
	int i=0;
	string val="";
	fstream book;
	book.open("Books.txt",ios::in|ios::out|ios::app);
	if(book)
	{
		while(getline(book,val))
		i++;
	}
	book.close();
	return i;
}
void remove()
{
	list();
	int totalBooks=fileSizeBook(),u=0;
	Book b[totalBooks],c[totalBooks-1];
	string idcheck;
	cout<<"Enter Book id: ";
	cin>>idcheck;
	fstream book;
	book.open("Books.txt",ios::in);
	if(book)
	{
		int i=0;
		u=0;
		while(i<totalBooks)
		{
			book>>b[i].id>>b[i].name>>b[i].stock>>b[i].price;
			if(b[i].id!=idcheck)
			{
				c[u]=b[i];
				u++;
			}
				i++;
		}
		removeByBook(idcheck);
		book.close();
	}
	
	book.open("Books.txt",ios::out);
	if(book)
	{
		int j=0;
		while(j<(sizeof(c)/sizeof(*c)))
		{
		book<<c[j].id<<"\t"<<c[j].name<<"\t"<<c[j].stock<<"\t"<<c[j].price<<"\n";
		j++;
		}
	
	}
	book.close();
	string file=idcheck+".txt";
	book.open(file.c_str(),ios::in|ios::out|ios::app);
	if(book)
	{
		book.close();
		remove(file.c_str());
	}
	cout<<"Book has been deleted";
	getch();
}
void issue()
{
	student s;
	cout<<"Enter Student id: ";
	cin>>s.id;
	cout<<"Enter Student name: ";
	cin>>s.name;
	cout<<"Enter Student Phone No.: ";
	cin>>s.phnNo;
	list();
	cout<<"\nEnter Book id: ";
	cin>>s.bookId;
	fstream stu;
	stu.open("students.txt",ios::in|ios::out|ios::app);
	if(stu)
	{
		stu<<"\n"<<s.id<<"\t"<<s.name<<"\t"<<s.bookId<<"\t"<<s.phnNo;
	}
	stu.close();
	string stock;
	string file=s.bookId+".txt";
	stu.open(file.c_str(),ios::out|ios::in);
	if(stu)
	{
		stu>>stock;
		stu.close();
		stu.open(file.c_str(),ios::in|ios::out);
		if(stu)
		{
			int st=atoi(stock.c_str())-1;
			stu<<std::to_string(st);
		}
	}
	cout<<"Book has been issued to student";
	getch();
}
void returnBook()
{
	listissued();
	int totalstu=fileSizestu(),u=0,index=0;
	student b[totalstu],c[totalstu-1];
	string idcheck;
	cout<<"Enter Student id: ";
	cin>>idcheck;
	fstream stu;
	stu.open("students.txt",ios::in);
	if(stu)
	{
		int i=0;
		u=0;
		while(i<totalstu)
		{
			stu>>b[i].id>>b[i].name>>b[i].bookId>>b[i].phnNo;
			if(b[i].id!=idcheck)
			{
				c[u]=b[i];
				u++;
			}
			else
			index=i;
				i++;
		}
		stu.close();
	}
	
	stu.open("students.txt",ios::out);
	if(stu)
	{
		int j=0;
		while(j<(sizeof(c)/sizeof(*c)))
		{
		stu<<"\n"<<c[j].id<<"\t"<<c[j].name<<"\t"<<c[j].bookId<<"\t"<<c[j].phnNo;
		j++;
		}
	
	}
	stu.close();
	string file=b[index].bookId+".txt",stock="";
	stu.open(file.c_str(),ios::in|ios::out|ios::app);
	if(stu)
	{
		stu>>stock;
		stu.close();
		stu.open(file.c_str(),ios::in|ios::out);
		if(stu)
		{
			int st=atoi(stock.c_str())+1;
			stu<<std::to_string(st);
		}
	}
	cout<<"Book has been deleted";
	getch();
}
void list()
{
	int totalBooks=fileSizeBook();
	Book b[totalBooks];
	fstream book;
	book.open("Books.txt",ios::in|ios::out);
	if(book)
	{
		int i=0;
		while(i<=totalBooks)
		{
			book>>b[i].id>>b[i].name>>b[i].stock>>b[i].price;
			i++;
		}
		
	}
	book.close();
	for(int k=0;k<totalBooks;k++)
	{
		cout<<endl<<"Book Id: "<<b[k].id<<endl;
		cout<<"Book Name: "<<b[k].name<<endl;
		cout<<"Stock: "<<b[k].stock<<endl;
	}
}
int fileSizestu()
{
	int i=0;
	string val="";
	fstream stu;
	stu.open("students.txt",ios::in|ios::out|ios::app);
	if(stu)
	{
		while(getline(stu,val))
		i++;
	}
	stu.close();
	return i;
}
void listissued()
{
	int totalstu=fileSizestu();
	student st[totalstu];
	fstream stu;
	if(totalstu==0)
	{
		cout<<endl<<"No Book is issued";
		getch();
		return;
	}
	stu.open("students.txt",ios::in|ios::out);
	if(stu)
	{
		int i=0;
		while(i<=totalstu)
		{
			stu>>st[i].id>>st[i].name>>st[i].bookId>>st[i].phnNo;
			i++;
		}
		
	}
	stu.close();
	for(int k=0;k<totalstu;k++)
	{
		cout<<endl<<"Student Id: "<<st[k].id<<endl;
		cout<<"Student Name: "<<st[k].name<<endl;
		cout<<"Id of Book Issued: "<<st[k].bookId<<endl;
		cout<<"Phone No. "<<st[k].phnNo<<endl;
	}
}
void mainMenu()
{
	menu:
	int action;
	system("cls");
	cout<<"############################Main Menu############################"<<endl<<endl;
	cout<<"\n1-Add new Book\n2-Delete Book\n3-Issue Book\n4-Return Book\n5-list All Books\n6-List all details of issued Books\n7-exit\nPress: ";
	cin>>action;
	switch(action)
	{
		case 1:
			add();
			break;
		case 2:
			remove();
			break;
		case 3:
			issue();
			break;
		case 4:
			returnBook();
			break;
		case 5:
			list();
			getch();
			break;
		case 6:
			listissued();
			getch();
			break;
		case 7:
			exit(0);
			break;
		default:
			{
				cout<<"Please Enter correct choice";
				getch();
				system("cls");
				goto menu;
			}
	
	}
	goto menu;
}
int main()
{
	login();
	mainMenu();
}
