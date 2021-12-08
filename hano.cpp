#include<bits/stdc++.h>
using namespace std;
int n;
/*
 * hanno函数的意义是把当前n个盘从start移到end,用temp作为中转站
 */
int hanno(int start,int end,int temp,int n)
{
    if(n-1>=1)//如果上面的部分起码还有一个，就还要拆 
        hanno(start,temp,end,n-1);//把小的群移到中转站,即从start移到temp,在这过程中end是充当临时存放的地方

    printf("%d -> %d ",start,end);//把底盘从start移到end

    if(n-1>=1)//如果上面的部分起码还有一个，就还要拆 
        hanno(temp,end,start,n-1);//把小的群从中转站移到终点，即从temp移到end,也就是这时候start是充当临时存放的地方
}

int main()
{
    
    hanno(1,3,2,1);
    printf("hanno");
    hanno(1,3,2,2);
    printf("hanno3");
    hanno(1,3,2,3);
    
}