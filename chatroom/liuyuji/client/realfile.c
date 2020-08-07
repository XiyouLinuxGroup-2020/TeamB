/*************************************************************************
	> File Name: realfile.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月07日 星期五 09时52分11秒
 ************************************************************************/

#include"client.h"
void *realfile(void *arg)
{
    //printf("realfile start\n");
    int len=0;
    //获取好友id
    char fid[10];
    if((len=get_arg(arg,fid,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    fid[len]=0;
    //printf("fid is %s\n",fid);//
    //获取文件路径
    char pathname[256];
    if((len=get_arg(arg,pathname,10))<0){
        fprintf(stderr,"get_arg failed\n");
    }
    pathname[len]=0;
    //printf("pathname is %s\n",pathname);//
    //从路径名中解析出文件名
    char filename[257];
    len=0;
    for(int i=0;i<strlen(pathname);i++){
        if(pathname[i]=='/'){
            len=0;
            continue;
        }
        filename[len++]=pathname[i];
    }
    filename[len]=0;
    FILE *fp=fopen(pathname,"r");
    char send_buf[1024];
    // 每读取一段数据，便将其发送给服务器，循环直到文件读完为止
    char buffer[513];
    memset(buffer,0,sizeof(buffer));
    while((len=fread(buffer,sizeof(char),512,fp)) > 0)
    {
        memset(send_buf,0,sizeof(send_buf));
        sprintf(send_buf,"%s\n%s",filename,buffer);
        //printf("realfile send_buf is %s",send_buf);//
        if(send_pack(connfd,REALFILE,strlen(send_buf),send_buf)<0){
            my_err("write",__LINE__);
        }
        memset(buffer,0,sizeof(buffer));
    }
    // 关闭文件
    fclose(fp);
    sleep(1);
    memset(send_buf,0,sizeof(send_buf));
    sprintf(send_buf,"%s\n%s\n%s\n",user_id,fid,filename);
    //printf("sendfile send_buf is %s",send_buf);//
    if(send_pack(connfd,SENDFILE,strlen(send_buf),send_buf)<0){
        my_err("write",__LINE__);
    }
    free(arg);
    P_LOCK;
    printf("文件已发送至服务器，等待好友接收\n");
    P_UNLOCK;
    pthread_exit(NULL);
}