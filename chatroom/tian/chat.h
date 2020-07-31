#ifndef _CHAT_H
#define _CHAT_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

#define EXIT          -1
#define REGISTE        1
#define LOGIN          2
#define ACCOUNT_ERROR -2

#define MAX_CHAR          200
#define FRI_MAX          300
#define BUFSIZE          1000




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
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    int statu_s;
    struct _relation *next;
}Relation;

typedef struct _recordinfo
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[BUFSIZE];
    struct _recordinfo *next;
}Recordinfo;

typedef struct _friends
{
    char friends[FRI_MAX][MAX_CHAR];
    int friends_status[FRI_MAX];
    int friends_num;
}FRI_INFO;

typedef struct _group
{
    char groups[FRI_MAX][MAX_CHAR];
    int grp_num;
}GROUP_INFO;

typedef struct _record
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[MAX_CHAR];
}RECORD_INFO;

typedef struct {
    char  file_name[MAX_CHAR];       
    char  file_send_name[MAX_CHAR];  
    char  file_recv_name[MAX_CHAR];  
    int   file_size;                 
    int   file_size_now;             
    int   flag ;                   
} FIle;

typedef struct {
    int               send_fd;
    int               recv_fd;
    char              send_user[50];
    char              recv_user[50];
    char              mes[MAX_CHAR];
} DATA;

typedef struct {
    int               type;
    DATA              data;
    FIle file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[55];
} PACK;



void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

#endif
