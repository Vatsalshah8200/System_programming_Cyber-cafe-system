//libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <time.h>
#include <string.h> 
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
//global variable
#define READ 0    /* The index of the “read” end of the pipe */
#define WRITE 1 /* The index of the “write” end of the pipe */
#define BUFFER_SIZE 1000
pthread_mutex_t mutexthread;
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
//0 inactive 1 active
struct user{
    unsigned int threadId;
    int status;
    char* username;
    struct pc pcdet;
    time_t login;
    time_t logout;
    struct Date date; 
    double min;
    double payment;
};


struct history
 {
     char username[50];
     double time;
     double cash;
 };
struct pc total_pc[10];
struct user login_users[10];

double prepaid;
// struct history record[100];
struct user temp;
pthread_t threadID[10];
int filed[10][2];
int err;
//functions
int intial_screen();
int login_newuser();
void * thread_login(void *arg);
void logout_user();
void write_logged_in();
int totalSizeString( char* str);
void Display_login_user();
void setcost();
void getpcstatus();
void changepcstatus();
void logoutall();
// int sendmsg();
void prepaidplan();
bool prepaiduserexsist(char* username);
void upgradePlanBalance();

bool check_username_exsist(char* username);
void write_history(int findpc);
int check_prepaid_deduct(int findpc);
char * findstringprepaid( char* word);
char * findstring( char* word);
char * makestringtoreplace(int findpc);
void replaceAll(char *str, const char *oldWord, const char *newWord);

double searchIncomeByUname(char* uname);
double searchIncomeByDate(char* date);
void getincome();

