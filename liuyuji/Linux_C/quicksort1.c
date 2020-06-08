#include<stdio.h>
#define ElementType int
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
ElementType Median3( ElementType A[], int Left, int Right )
{ 
    int Center = (Left+Right) / 2;
    if ( A[Left] > A[Center] )
        swap( &A[Left], &A[Center] );
    if ( A[Left] > A[Right] )
        swap( &A[Left], &A[Right] );
    if ( A[Center] > A[Right] )
        swap( &A[Center], &A[Right] );
    /* 此时A[Left] <= A[Center] <= A[Right] */
    swap( &A[Center], &A[Right-1] ); /* 将基准Pivot藏到右边*/
    /* 只需要考虑A[Left+1] … A[Right-2] */
    return  A[Right-1];  /* 返回基准Pivot */
}
 
void Qsort( ElementType A[], int Left, int Right )
{ /* 核心递归函数 */ 
     int Pivot, Cutoff, Low, High;
     Cutoff=1;  
     if ( Cutoff <= Right-Left ) { /* 如果序列元素充分多，进入快排 */
          Pivot = Median3( A, Left, Right ); /* 选基准 */ 
          Low = Left; High = Right-1;
          while (1) { /*将序列中比基准小的移到基准左边，大的移到右边*/
               while ( A[++Low] < Pivot ) ;
               while ( A[--High] > Pivot ) ;
               if ( Low < High ) swap( &A[Low], &A[High] );
               else break;
          }
          swap( &A[Low], &A[Right-1] );   /* 将基准换到正确的位置 */ 
          Qsort( A, Left, Low-1 );    /* 递归解决左边 */
          Qsort( A, Low+1, Right );   /* 递归解决右边 */  
     }
     else printf("用简单排序\n");//InsertionSort( A+Left, Right-Left+1 ); /* 元素太少，用简单排序 */ 
}
 
void QuickSort( ElementType A[], int N )
{ /* 统一接口 */
     Qsort( A, 0, N-1 );
}
int main()
{
    int A[1000]={
1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,534
,1,3,20,43,2,7,4,87,34,65,12,77,11,34,6,7,8,53,2,23,199,55,43,4,34,76,433,6,4,3,2,55,6,3,66,32,5,67,32,2,6,66,7,8,7,9,0,8,7,62,3,4,5,6,7,9,3,4,5,6,2,45,6,7,98,5,34,2,4,6,78,9,67,59,64,22,4,5,60,70,89,61,4,322,23,226,744,8,6,65,533,422,344,264,233,367,434,444,55,20
};
    QuickSort(A,1000);
    for(int i=0;i<1000;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    return 1;
}