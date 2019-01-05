#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAX 100
int m=0,sum=0;//sum用于计算运算符的个数

char JC='0';
char str[MAX];//用于存输入表达式
int  token=0;//左括号的标志


void change(int e)
{

	int f=e+2;
	char ch=str[f];
	if(ch>='A'&&ch<='Z')
	{
		for (int l=0; l<m+10; l++) {
			if(str[l]==ch)
				str[l]=JC;
		}
	}

	if(str[e]>='A'&&str[e]<='Z')
	{
		for(int i=0; i<m; i++)
		{
			if(str[i]==str[e])
				str[i]=JC;
		}
	}

}

void chengchuchuli(int i,int m)
{

	i++;
	for( ;i<=m-1;i++)//处理乘除运算
	{
		if(str[i]=='*'||str[i]=='/')
		{

			cout<<"("<<JC<<" "<<str[i]<<" "<<str[i-1]<<" "<<str[i+1]<<")"<<endl;
			change(i-1);
			str[i-1]=str[i]=str[i+1]=JC;
			sum--;
            JC++;
		}
	}
}

void jiajianchuli(int j,int m)
{
	j++;
	for( ;j<=m-1;j++)////处理加减运算
	{
		if(str[j]=='+'||str[j]=='-')
		{
			cout<<"("<<JC<<" "<<str[j]<<" "<<str[j-1]<<"  "<<str[j+1]<<")"<<endl;
			change(j-1);
			str[j-1]=str[j]=str[j+1]=JC;
			sum--;
			JC++;
		}

	}
}

void scan(FILE *fin)
{
	//int p[MAX];
	char st[MAX];
	char ch='a';
	//int c=-1,q=0;
	while(ch!=EOF)
	{
		ch=getc(fin);

		while(ch==' '||ch=='\t') ch=getc(fin);

		str[m++]=ch;

		if(ch=='='||ch=='+'||ch=='-'||ch=='*'||ch=='/') sum++;


	}


	int mm = 0;
	for (int i = 0; i < m - 1; ++i){
		st[mm++] = str[i];
	}

	m = mm;
	for (int i = 0; i < m; ++i) str[i] = st[i];
}

void siyuanshi()
{
    int p[MAX];
    int c=0,q=0;
    int iii=0;
    for(int ii=0;ii<=m-1;ii++){
            if(str[ii]=='\n'){
    for(int w=iii;w<=ii-1;w++){
        if(str[w]=='(')
		{
			p[c]=w;

		}
		else if(str[w]==')')
		{
			q=w;
			chengchuchuli(p[c],q);//从左括号处理到右括号
			jiajianchuli(p[c],q);
			JC++;
			str[p[c]]=str[w]=JC;
			JC++;

		}
	}

	for(int i=iii;i<=ii-1;i++)//处理乘除运算
	{
		if(str[i]=='*'||str[i]=='/')
		{

			cout<<""<<JC<<" ("<<str[i]<<" "<<str[i-1]<<" "<<str[i+1]<<")"<<endl;
			change(i-1);
			str[i-1]=str[i]=str[i+1]=JC;
			sum--;
			JC++;
		}

	}

	for(int j=iii;j<=ii-1;j++)//处理加减运算
	{
		if(str[j]=='+'||str[j]=='-')
		{

			cout<<""<<JC<<" ("<<str[j]<<" "<<str[j-1]<<" "<<str[j+1]<<")"<<endl;
			change(j-1);
			str[j-1]=str[j]=str[j+1]=JC;
			sum--;
			JC++;
		}

	}

	for(int k=iii;k<=ii-1;k++)//处理赋值
	{
		if(str[k]=='=')
		{


			cout<<""<<JC<<" ("<<str[k]<<" "<<str[k+1]<<" "<<str[k-1]<<")"<<endl;
			sum--;
			change(k+1);
			str[k-1]=JC;
			JC++;
		}
	}
    iii=ii;
    }
    }
}

int main(){
	char in[MAX];
	FILE *fin;
	fin=fopen("examplse2.txt","r");
	cout<<"三元式如下	"<<endl;

	scan(fin);
    siyuanshi();
	cout<<"SUCCESS"<<endl;
	fclose(fin);

}
