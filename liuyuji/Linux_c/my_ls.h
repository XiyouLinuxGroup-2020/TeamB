/*************************************************************************
	> File Name: my_ls.h
	> Author: 
	> Mail: 
	> Created Time: 2020年02月24日 星期一 16时36分06秒
 ************************************************************************/

#ifndef _MY_LS_H
#define _MY_LS_H

#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<Linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
void print_finfo(struct stat buf,char *name);
void print_fname(char *name);
void my_err(const char *err_string,int line);

#endif
