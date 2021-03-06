/*************************************************************************
	> File Name: queue.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月21日 星期六 20时58分58秒
 ************************************************************************/
//队列
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int date;
    struct node *next;
}Node;
typedef struct queue{
    Node *head;
    Node *tail;
    int num;
    int len;
}Queue;
void look(Queue *p)
{
    if(p->head==NULL){
        printf("队列为空\n");
        return;
    }
    Node *operate=p->head;
    printf("%d\n",operate->date);
}
int full(Queue *p)
{
    if(p->len==p->num){
        return 1;
    }
    else{
        return 0;
    }
}
void create(Queue *p,int n)
{
    p->num=n;
    p->head=NULL;
    p->tail=NULL;
    p->len=0;
}
int insert(Queue *p,int buf)
{
    if(full(p)==1){
        printf("队列已满\n");
        return 0;
    }
    Node *operate,*record;
    operate=(Node *)malloc(sizeof(Node));
    if(p->head==NULL){
        p->head=operate;
    }
    else{
        record=p->tail;
        record->next=operate;
    }
    operate->date=buf;
    p->tail=operate;
    p->len++;
    return 0;
}
void rm(Queue *p)
{
    if(p->head==NULL){
        printf("队列为空\n");
        return;
    }
    Node *operate=p->head;
    Node *record=operate->next;
    free(operate);
    p->head=record;
    p->len--;
}
void del(Queue *p)
{
    Node *operate,*record;
    operate=p->head;
    for(int i=0;i<p->len;i++){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
int main()
{
    printf("请输入队列长度\n");
    int num;
    scanf("%d",&num);
    Queue q;
    create(&q,num);
    while(1){
        printf("1.入队\n2.出队\n3.查看队头\n4.清空\n");
        int chose,a;
        scanf("%d",&chose);
        switch(chose){
            case 1:
                while(1){
                    if(full(&q)==1){
                        printf("队列已满\n");
                        break;
                    }
                    scanf("%d",&a);
                    insert(&q,a);
                    printf("继续？\n");
                    int temp;
                    scanf("%d",&temp);
                    if(temp==0){
                        break;
                    }
                }
                break;
            case 2:
                rm(&q);
                break;
            case 3:
                look(&q);
                break;
            case 4:
                del(&q);
                exit(0);
        }
    }
}
