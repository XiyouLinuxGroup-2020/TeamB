#ifndef _CHAT_H
#define _CHAT_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
#include<mysql.h>
#include<sys/epoll.h>

#define EXIT           -1
#define REGISTE         1
#define LOGIN           2
#define LOOK_FRI        3
#define GET_FRI_STA     4
#define ADD_FRI         5
#define DEL_FRI         6
#define SHI_FRI         7
#define REL_FRI         8 
#define CRE_GRP         9 
#define ADD_GRP         10 
#define OUT_GRP         11 
#define DEL_GRP         12 
#define SET_GRP         13 
#define KICK_GRP        14 
#define CHECK_GRP       15 
#define CHECK_MUM_GRP   16 
#define CHAT_FRI        17 
#define CHAT_GRP        18 
#define CHECK_MES_FRI   19 
#define CHECK_MES_GRP   20


#define FRIEND          1
#define FRI_BLK         2
#define GRP             3
#define GRP_OWN         4
#define GRP_ADM         5

#define OFFLINE         0
#define ONLINE          1
#define FRI_CHAT        2
#define GRP_CHAT        3

#define MAX_CHAR        200
#define FRI_MAX         100

#define SERV_PORT       8017 
#define LISTENQ         10
#define MAX_EVENTS      1000

typedef struct _user
{
    char name[MAX_CHAR];
    char passwd[MAX_CHAR];
    int statu_s;
    int fd;
    char chat[MAX_CHAR];
    struct _user *next;
}User;

typedef struct _relation
{
    char user[MAX_CHAR];
    char other_user[MAX_CHAR];
    int relation;
    struct _relation *next;
}Relation;

typedef struct _recordinfo
{
    char user[MAX_CHAR];
    char other_user[MAX_CHAR];
    char message[1024];
    struct _recordinfo *next;
}Recordinfo;

typedef struct 
{
    char friends[FRI_MAX][MAX_CHAR];
    int friends_status[FRI_MAX];
    int friends_num;
}FRI_INFO;

typedef struct 
{
    char groups[FRI_MAX][MAX_CHAR];
    int grp_num;
}GROUP_INFO;

typedef struct 
{
    char user[MAX_CHAR];
    char other_user[MAX_CHAR];
    char message[MAX_CHAR];
}RECORD_INFO;

typedef struct 
{
    int send_fd;
    int recv_fd;
    char send_name[MAX_CHAR];
    char recv_name[MAX_CHAR];    
    char mes[MAX_CHAR * 3];
}DATA;

typedef struct 
{
    int size;
    char mes[200];
}FIle;

typedef struct 
{
    int type;
    DATA data;
    FIle file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[100];
}PACK;

typedef struct 
{
    char file_name[10][MAX_CHAR];
    char file_send_name[10][MAX_CHAR];
    int sign_file;
}File;

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;

PACK Mex_Box[100];
int sign;
int sign_1;
File file;

User *User_list();     
Relation *Relation_list();         
Recordinfo *Record_list();
void Insert(User *pNew);
void Insert_RC(Recordinfo *pNew);
void Insert_R(Relation *pNew);
void Delete_R(Relation *pNew);
		
void *deal(void *recv_pack_t);
void registe(PACK *recv_pack);
void login(PACK *recv_pack);
void look_fri(PACK *recv_pack);
void get_fri_sta(PACK *recv_pack);  
void add_fri(PACK *recv_pack);      
void del_fri(PACK *recv_pack);    
void shi_fri(PACK *recv_pack);      
void rel_fri(PACK *recv_pack);     
void chat_fri(PACK *recv_pack);  
void check_mes_fri(PACK *recv_pack);
void cre_grp(PACK *recv_pack);
void add_grp(PACK *recv_pack);
void out_grp(PACK *recv_pack);
void del_grp(PACK *recv_pack);
void set_grp(PACK *recv_pack);
void kick_grp(PACK *recv_pack);
void check_grp(PACK *recv_pack);
void check_mum_grp(PACK *recv_pack);
void chat_grp(PACK *recv_pack);
void check_mes_grp(PACK *recv_pack);
void send_mes(int fd, int flag, PACK *recv_pack, char *mes);
void send_pack(int fd, PACK *recv_pack, char *ch);

#endif
