#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SourceMaxLength 10000
//声明函数
void A();
void B();
void F();
void T();
 
//字符串结构体
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
void error()//错误输出操作
{
    flag=0;
    printf("error;");
}
void E()//开始判断函数
{
    token=getToken();
    if(token != '(' && token!='i')//如果下一个当前取得的字符不为（、i，则字符串错误
        error();
    else{
        if(token=='('){//如果为（，执行()，并取下一个字符
            E();
            token=getToken();
            if(token!=')')
                error();
 
        }
        B();
        A();
    }
}
 
void T()//非终结符T判断
{
    token=getToken();
    if(token != '(' && token!='i')//如果下一个当前取得的字符不为（、i，则字符串错误
        error();
    else
    {
        if(token=='('){
            E();
            token=getToken();
            if(token!=')')
                error();
 
        }
        B();
    }
}
 
void F()//非终结符F判断
{
    token=getToken();
    if(token != '(' && token!='i')
        error();
    else
    {
        if(token=='('){
            E();
            token=getToken();
            if(token!='(') error();
        }
        else{
            ;
        }
    }
}
 
void A()//非终结符A判断
{
    token=getToken();
    if(token!='+'&&token!=')'&&token!='#')//如果当前字符不符合，输出错误
        error();
    else{
        if(token=='+')
        {
            T();
            A();
        }else{//如果A终结符为空，字符串指针回溯一个
            sour.pointer--;
        }
    }
}
void B()
{
    token=getToken();
    if(token!='*'&&token!='+'&&token!=')'&&token!='#')//如果当前字符不符合，输出错误
        error();
    else{
        if(token=='*')
        {
            F();
            B();
        }else{//如果B终结符为空，字符串指针回溯一个
            sour.pointer--;
        }
    }
}
 
int main()
{
    sour.pointer=0;
    strcpy(sour.source,"(i+i*i)+i*i#");//将字符串复制给sour.source
 
    //首先执行初始非终结符
    E();
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