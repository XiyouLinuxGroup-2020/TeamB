/*************************************************************************
	> File Name: 6.4.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月17日 星期五 20时24分01秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    double a[8],b[8];
    int i,j,k;
    for(i=0;i<8;i++){
        scanf("%lf",&a[i]);
    }
    for(i=0;i<8;i++){
        k=0;
        for(j=0;j<=i;j++){
            k+=a[j];
        }
        b[i]=k;
        printf("%lf ",b[i]);
    }
}