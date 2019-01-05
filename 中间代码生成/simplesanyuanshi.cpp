#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdlib.h>
using namespace std;

int m=0;

char Index='0';
char str[100];//用于存输入表达式
int  token=0;//左括号的标志

void scan(FILE *fin)
{
	char ch='a';
	cout<<"code is :"<<endl;
	while(ch!=EOF)
	{
		ch=getc(fin);
		cout<<ch;
		while(ch==' '||ch=='\t') { ch=getc(fin);cout<<ch;}
		str[m++]=ch;
	}
	cout<<endl;
}

void suojin(int zuo,int you)
{
	int i=0,cha=you-zuo;
	for(i=zuo;i<m;i++)
		str[i]=str[i+cha+1];
}

void sanyuanshi()
{
    int p[100];
    int c=0,q=0;
    int iii=0;
    for(int ii=0;ii<=m-1;ii++)
	{
		if(str[ii]=='\n')
		{
			for(int i = iii;i<=ii;i++) cout<<str[i];
			cout<<endl;
			for(int i=iii;i<=ii-1;i++)//处理乘除运算
			{
				if(str[i]=='*'||str[i]=='/')
				{

					if(str[i-1]==')' && str[i+1]==')')
					{
						cout<<""<<Index<<" ("<<str[i]<<" "<<"("<<str[i-2]<<")"<<" "<<"("<<str[i+2]<<")"<<")"<<endl;
						str[i-2]=Index;
						suojin(i,i+3);
						ii = ii-4;
						m = m-4;
					}
					else if(str[i-1]==')')
					{
						cout<<""<<Index<<" ("<<str[i]<<" "<<"("<<str[i-2]<<")"<<" "<<str[i+1]<<")"<<endl;
						str[i-2]=Index;
						suojin(i,i+1);
						ii = ii-2;
						m = m-2;
					}
					else if(str[i+1]=='(')
					{
						cout<<""<<Index<<" ("<<str[i]<<" "<<str[i-1]<<" "<<"("<<str[i+2]<<")"<<")"<<endl;
						str[i-1]='(';
						str[i]=Index;
						str[i+1]=')';
						suojin(i+2,i+3);
						ii = ii-2;
						m = m-2;
					}
					else
					{
						cout<<""<<Index<<" ("<<str[i]<<" "<<str[i+1]<<" "<<str[i-1]<<")"<<endl;
						str[i-1]='(';
						str[i]=Index;
						str[i+1]=')';
					}
					Index++;
				}

			}

			for(int j=iii;j<=ii-1;j++)//处理加减运算
			{
				if(str[j]=='+'||str[j]=='-')
				{
					if(str[j-1]==')' && str[j+1]=='(')
					{
						cout<<""<<Index<<" ("<<str[j]<<" "<<"("<<str[j-2]<<")"<<" "<<"("<<str[j+2]<<")"<<")"<<endl;
						str[j-2]=Index;
						suojin(j,j+3);
						ii = ii-4;
						m = m-4;
					}
					else if(str[j-1]==')')
					{
						cout<<""<<Index<<" ("<<str[j]<<" "<<"("<<str[j-2]<<")"<<" "<<str[j+1]<<")"<<endl;
						str[j-2]=Index;
						suojin(j,j+1);
						ii = ii-2;
						m = m-2;
					}
					else if(str[j+1]=='(')
					{
						cout<<""<<Index<<" ("<<str[j]<<" "<<str[j-1]<<" "<<"("<<str[j+2]<<")"<<")"<<endl;
						str[j-1]='(';
						str[j]=Index;
						str[j+1]=')';
						suojin(j+2,j+3);
						ii = ii-2;
						m = m-2;
					}
					else
					{
						cout<<""<<Index<<" ("<<str[j]<<" "<<str[j+1]<<" "<<str[j-1]<<")"<<endl;
						str[j-1]='(';
						str[j]=Index;
						str[j+1]=')';
					}
					Index++;
				}

			}

			for(int k=iii;k<=ii-1;k++)//处理赋值
			{
				if(str[k]=='=')
				{
					if(str[k+1]=='(')
					{
						cout<<""<<Index<<" ("<<str[k]<<" "<<str[k-1]<<" "<<"("<<str[k+2]<<")"<<")"<<endl;
						str[k-1]='(';
						str[k]=Index;
						str[k+1]=')';
						suojin(k+2,k+3);
						ii = ii-2;
						m = m-2;
					}
					else
					{
						cout<<""<<Index<<" ("<<str[k]<<" "<<str[k+1]<<" "<<str[k-1]<<")"<<endl;
						str[k-1]='(';
						str[k]=Index;
						str[k+1]=')';
					}
					Index++;
				}
			}
			iii=ii;
		}
    }
}

int main()
{
	system("chcp 65001");
	cout<<endl;
	FILE *fin;
	fin=fopen("examplse2.txt","r");
	scan(fin);
	cout<<"三元式如下:	"<<endl;
    sanyuanshi();
	cout<<endl<<"successful !"<<endl;
	fclose(fin);
	char car;
	cin>>car;
	return 0;
}
