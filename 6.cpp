#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SourceMaxLength 10000
//声明函数
void A();
void B();

//结构体存放待比较字符串
struct sourceStr{
    char source[SourceMaxLength];//缓存字符串
    int pointer;//字符串下表指针
};
struct sourceStr sour;
char token;//存放当前比较的字符
int flag=1;//编译成功标记
char getToken()//获取当前字符
{
    token=sour.source[sour.pointer];
    sour.pointer++;
    return token;
}
void getSource(FILE *fp)//用于从文件中获取字符串
{

}
void error()//错误输出操做
{
    flag=0;
    printf("error;");
}
void S()//开始判断函数
{
    token=getToken();
    if(token != 'p' && token!='q')//若是下一个当前取得的字符不为p\q，则字符串错误
        error();
    else
    {
        if(token == 'p')//若是当前字符为p
        {
            A();//执行非终结符A的判断
        }
        else//不然执行非终结符B的判断
        {
            B();
        }
    }
}
void A()//执行非终结符A的判断
{
    token=getToken();
    if(token!='c'&&token!='a')//若是当前字符不符合，输出错误
        error();
    else{
        if(token=='c')//若是为c,则执行A判断
        {
            A();
            //判断下一个字符是否为d
            token=getToken();
            if(token!='d')
                error();
        }
        else{
            ;
        }
    }
}

void B()//执行非终结符A的判断
{
    token=getToken();
    if(token!='d'&&token!='b')//若是当前字符不符合，输出错误
        error();
    else{
        if(token=='d')//若是为d，执行B函数
        {
            B();
        }
    }
}

int main()
{
    sour.pointer=0;
    strcpy(sour.source,"pcad");//将字符串复制给sour.source

    //首先执行初始非终结符
    S();
    if(flag==1)
    {
        printf("success!");
    }
    else
    {
        printf("error");
    }
    return 0;
}