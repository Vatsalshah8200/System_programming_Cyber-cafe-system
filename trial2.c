//login logout threading
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int out[10]={0,0,0,0,0,0,0,0,0,0};
struct pc
{
    int pc_no;
    int status;
};
struct user{
    char* username;
    struct pc pcdet;
    // time_t login;
    // time_t logout;
    // struct Date date; 
    // double min;
};
void * thread_fn_multiple_param(void *arg)
{
    printf("thread id %u is starting \n", (unsigned int)pthread_self());
	struct user *thread_p = arg;
	printf("Thread with One Param: %d + %s\n", thread_p->pcdet.pc_no, thread_p->username);
	printf("thread id %u is exiting 1 \n", (unsigned int)pthread_self());
    while(1){if(out[thread_p->pcdet.pc_no-1]==1)return thread_p;}
   // pthread_exit((void *) thread_p->pcdet);
    //return thread_p;
}
void * exit_thread(void *arg)
{
    printf("thread id %u is starting \n", (unsigned int)pthread_self());
    int l;
    printf("enter pc no to logout --------------\n");
    scanf("%d",&l);
    out[l-1]=1;
    int j;
    printf("enter pc no to logout--------------\n");
    scanf("%d",&j);
    out[j-1]=1;
    printf("thread id %u is exiting 2\n", (unsigned int)pthread_self());
}

int main()
{
    pthread_t threadID;
    pthread_t threadID2;
    pthread_t threadID3;
    printf("main thread id %u is starting \n", (unsigned int)pthread_self());
	struct user p;
    struct user p2;
	p.username = "vatsal";
	p.pcdet.pc_no = 5;
    p.pcdet.status = 1;
	int err = pthread_create (&threadID, NULL, thread_fn_multiple_param, (void *)&p);

	if (err != 0)
			printf("cant create thread: %s\n", strerror(err));

    p2.username = "Neel";
	p2.pcdet.pc_no = 3;
    p2.pcdet.status = 1;
    err = pthread_create (&threadID2, NULL, thread_fn_multiple_param, (void *)&p2);

	if (err != 0)
			printf("cant create thread: %s\n", strerror(err));
   // pthread_exit((void *) thread_p->pcdet);
	// wait for thread creation and execution
   // void * n = pthread_exit(&threadID);
   
    //void * f = pthread_exit(&threadID2);

    err = pthread_create (&threadID3, NULL, exit_thread, NULL);
    
    struct user *n, *f;
    err = pthread_join(threadID, (void **)&n);
     if (err != 0)
		printf("cant join with thread1: %s\n", strerror(err));
    printf("%d\n",(n->pcdet.pc_no));
     err = pthread_join(threadID2, (void **)&f);
    if (err != 0)
		printf("cant join with thread1: %s\n", strerror(err));
    printf("%d\n",(f->pcdet.pc_no));

	printf("main thread id %u is exiting \n", (unsigned int)pthread_self());
}
