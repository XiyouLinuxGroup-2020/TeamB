/*************************************************************************
	> File Name: dealfriend.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月13日 星期四 15时40分07秒
 ************************************************************************/

#include"client.h"
int dealfriend()
{
    FR_LOCK;
    if(Frh.num==0){
        printf("\t\t\t\t\t您暂时没有好友验证消息\n");
        FR_UNLOCK;
        return 0;
    }
    Freq *operate=Frh.head;
    int chose=0;
    char send_buf[1024];
    while(operate){
        memset(send_buf,0,sizeof(send_buf));
        P_LOCK;
        printf("%s申请添加您为好友\n",operate->send_id);
        printf("1.同意\t\t2.拒绝\n");
        P_UNLOCK;
        scanf("%d",&chose);
        switch(chose){
            case 1:
            sprintf(send_buf,"%s\n%s\n1\n",user_id,operate->send_id);
            if(send_pack(connfd,DEALFRIEND,strlen(send_buf),send_buf)<0){
                my_err("write",__LINE__);
            }
            break;
            case 2:
            sprintf(send_buf,"%s\n%s\n2\n",user_id,operate->send_id);
            if(send_pack(connfd,DEALFRIEND,strlen(send_buf),send_buf)<0){
                my_err("write",__LINE__);
            }
            break;
        }
        operate=operate->next;
    }
    delfrnode();
    FR_UNLOCK;
}