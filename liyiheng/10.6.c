#include<stdio.h>
int main()
{
    double a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}},b[3][4];
    int i,j;
    for(i=0;i<3;i++)
      for(j=0;j<4;j++)
     b[i][j]=a[i][j];
    for(i=0;i<3;i++)
    {
      for(j=0;j<4;j++)
       {printf("%lf",b[i][j]);
        if(j!=0)
        printf(" ");
       }
    printf("\n");
    }


}















    

