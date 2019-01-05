#include<stdio.h>
#include<string.h>
#include<stdbool.h>
void Print();
void Scanner();

int syn;//存放单词的类型
char *wordtype[5] = {"保留字","运算符","标志符","常数","界符"};
int p;

char ch;
int sum;//用来保存数字的值
char program[1000],token[15];
char *rwtab[13]={"begin","if","then","procedure","odd","call","else","while","do","const","var","end","do"};
int m;

bool isDigital(char ch)
{
    if(ch<='9'&&ch>='0')
        return true;
    else
        return false;
}

bool isAlpha(char ch)
{
    if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
        return true;
    else
        return false;
}


void Scanner()
{
    int num=0;
    int n;
    for(m=0;m<15;m++)
    {
        token[m]='\0';
    }
    m=0;
    ch=program[p++];

    while(ch==' '||ch=='\n'||ch=='\t')
    {
        ch=program[p++];
    }
    if(isAlpha(ch)){
        do{
            token[m++]=ch;
            ch=program[p++];
        }while(isAlpha(ch)||isDigital(ch));
        p--;
        syn=2;
        token[m++]='\0';
        for(n=0;n<13;n++)
        {
            if(strcmp(token,rwtab[n])==0)
            {
                syn=0;
                break;
            }
        }
        return;
    }
    else if(isDigital(ch))
    {
        sum=0;
        while(isDigital(ch))
        {
            sum=sum*10+ch-'0';
            ch=program[p++];
        }
        p--;
        syn=3;
        if(isAlpha(ch))
            syn=-1;
        return;
    }
    else
    {
        token[0]=ch;
        switch(ch)
        {
            case '<':ch=program[p++];
                    if(ch=='>')
                    {
                        syn=1;
                        token[1]=ch;
                    }
                    else if(ch=='=')
                        {
                            syn=1;
                            token[1]=ch;
                        }
                    else{
                        syn=1;
                        p--;
                    }
                    break;
            case '>':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=1;
                        token[1]=ch;
                    }
                    else{
                        syn=1;
                        p--;
                    }
                    break;
            case '=':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=1;
                        token[1]=ch;
                    }
                    else{
                        syn=1;
                        p--;
                    }
                    break;
            case '+':syn=1;break;
            case '-':syn=1;break;
            case '*':syn=1;break;
            case '/':syn=1;break;
            case ';':syn=4;break;
            case '(':syn=4;break;
            case ')':syn=4;break;
            case ',':syn=4;break;
            case '#':syn=-2;break;
            case ':':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=1;
                        token[1]=ch;
                    }
                    else{
                        syn=4;
                        p--;
                    };break;

            default:syn=-1;break;
        }
        return;
    }
}

void Print()
{
    if(syn==3)
        printf("<%s,%d>\n",wordtype[syn],sum);
	else if(syn==-2) {}
    else
        printf("<%s,%s>\n",wordtype[syn],token);
}


int main()
{
    printf("输入词法分析串以#作为结束\n");
    do
    {
        ch=getchar();
        program[p++]=ch;
    }while(ch!='#');
    p=0;
	int i=0;
	//printf("%s",wordtype[0]);
    //printf("%s\n",program);
    do{
        Scanner();
        switch(syn)
        {
            case -1:for(i=p-1;i<=p;i++) printf("%c",program[i]);printf("      "); printf("is wrong\n",token);break;
            default:Print();break;
        }
    }while(syn!=-2);
    if(syn==-2)printf("success\n\n");
}
