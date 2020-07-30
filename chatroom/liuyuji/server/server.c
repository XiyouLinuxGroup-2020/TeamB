/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月27日 星期一 19时34分28秒
 ************************************************************************/

#include"chat.h"
#include"thread_pool.h"
void my_err(const char *str,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(str);
    exit(1);
}
void setnoblock(int sock)
{
    int flag=fcntl(sock,F_GETFL);
    if(flag<0){
        my_err("fcntl",__LINE__);
        exit(1);
    }
    flag|=O_NONBLOCK;  
    if(fcntl(sock,F_SETFL,flag)<0)  
    {  
        my_err("fcntl(sock,SETFL,opts)",__LINE__);  
        exit(1);  
    }
}
int main()
{
    //log=fopen("log","w");
    //初始化线程私有数据
    pthread_key_create(&key,NULL);

    //初始化服务器TCP套接字
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        my_err("socket",__LINE__);
    }
    
    //设置套接字可重新绑定端口
    int opt=1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt))<0){
        my_err("setsockopt",__LINE__);
    }
    
    //初始化服务器地址
    struct sockaddr_in listenfd_addr;
    memset(&listenfd_addr,0,sizeof(struct sockaddr_in));
    listenfd_addr.sin_family=AF_INET;
    listenfd_addr.sin_port=htons(SERV_PORT);
    listenfd_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
    //绑定服务器地址
    if(bind(listenfd,(struct sockaddr*)&listenfd_addr,sizeof(struct sockaddr))<0){
        my_err("bind",__LINE__);
    }
    
    //转为监听套接字
    if(listen(listenfd,20)<0){
        my_err("listen",__LINE__);
    }
    //fprintf(log,"listen socket %d had been done\n",listenfd);

    //初始化数据库
    if(NULL == mysql_init(&mysql)){
		my_err("mysql_init", __LINE__);
	}
    if(mysql_library_init(0, NULL, NULL) != 0){
		my_err("mysql_library_init", __LINE__);
	}
    
    //连接数据库
    if(NULL == mysql_real_connect(&mysql, "127.0.0.1", "root", "Lyj011007.", "chatroom", 0, NULL, 0)){
		my_err("mysql_real_connect", __LINE__);
	}
	
    //设置中文字符集
	if(mysql_set_character_set(&mysql, "utf8") < 0){
		my_err("mysql_set_character_set", __LINE__);
	}
	//fprintf(log,"连接mysql数据库成功!\n");

    //初始化线程池
    pool_init(6);
    
    //初始化epoll
    int epfd=epoll_create(20);
    if(epfd<0){
        my_err("epoll_create",__LINE__);
    }
    struct epoll_event ev;
    
    //将epoll设置为ET模式
    ev.events=EPOLLIN | EPOLLET;
    ev.data.fd=listenfd;
    
    //将listenfd设置为非阻塞
    setnoblock(listenfd);

    //将listenfd加入到epoll中
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev)<0){
        my_err("epoll_ctl",__LINE__);
    }

    //处理连接请求
    int event_num=0;
    struct sockaddr_in client_addr;
    struct epoll_event ep_events[20];
    int client_addr_len=sizeof(struct sockaddr);
    int connfd;
    while(1){
        event_num=epoll_wait(epfd,ep_events,20,-1);
        for(int i=0;i<event_num;i++){
            //若有客户端连接
            if(ep_events[i].data.fd==listenfd){
                if((connfd=accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len))<0){
                    my_err("accept",__LINE__);
                }
                //fprintf(log,"client %s connect\n",inet_ntoa(client_addr.sin_addr));
                //设置为非阻塞
                setnoblock(connfd);
                
                ev.data.fd=connfd;
                ev.events=EPOLLIN | EPOLLET | EPOLLHUP;
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            //若有客户请求
            else if(ep_events[i].events & EPOLLIN){
                //将解包函数放入线程池
                add_work(unpack,&ep_events[i].data.fd);
                //printf("add_work\n");
                //pthread_t tid;//
                //pthread_create(&tid,NULL,unpack,&ep_events[i].data.fd);
                //unpack(&ep_events[i].data.fd);
            }
            //若客户挂断
            else if(ep_events[i].events & EPOLLHUP){
                close(ep_events[i].data.fd);  
                epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
                //fprintf(log,"%d is be closed\n",ep_events[i].data.fd);
            }
        }
    }
    close(listenfd);
    pool_destroy();
    close(epfd);
    pthread_key_delete(key);
    return 0;
}