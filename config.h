//libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <time.h>
#include <string.h> 
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
//global variable
//0-login,1-logout,2-not in use
int out[10]={2,2,2,2,2,2,2,2,2,2};

double per_hour_cost = 0;
//structures
//0 = off 1 = on
struct pc
{
    int pc_no;
    int status;
};
struct Date
{
    int day;
    int month;
    int year;
};
struct user{
    unsigned int threadId;
    char* username;
    struct pc pcdet;
    time_t login;
    time_t logout;
    struct Date date; 
    double min;
    double payment;
};
struct pc total_pc[10];
struct user login_users[10];
struct user temp;
pthread_t threadID[10];
int err;
//functions
int intial_screen();
int login_newuser();
void * thread_login(void *arg);
void logout_user();
void write_logged_in();
int totalSizeString(const char* str);
void Display_login_user();
