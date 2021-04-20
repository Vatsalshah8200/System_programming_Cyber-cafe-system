#include "config.h"


void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int intial_screen()
{
    for(int i=0;i<10;i++)
    {
        total_pc[i].pc_no = i;
        total_pc[i].status = 0;
    }
    int choice;
    printf("\n");
    printf("1: NewLogin\n");
    printf("2: Logout\n");
    printf("3: Logged IN Users\n");
    printf("4: Set Per Hour Cost\n");
    printf("5: Logout All The Users\n");
    printf("6: Get pc Status\n");
    printf("7: Switch on/of PC\n");
    printf("8: calculate Total Income\n");
    printf("Enter your choice from 1 - 8 : ");

    scanf("%d",&choice);
    printf("\n");
    clean_stdin();
    return choice;
}


void Display_login_user()
{
    printf("\n");
    for(int i=0;i<10;i++)
    {
        if(login_users[i].pcdet.status==1)
        {
            printf("pc No. : %d \n" ,login_users[i].pcdet.pc_no);
            printf("Username : %s \n",login_users[i].username);
            printf("ThreadId : %u \n",login_users[i].threadId);

            login_users[i].logout=time(NULL);
            double sec=difftime(login_users[i].logout,login_users[i].login);
            double h = (sec/3600); 
            login_users[i].min = (sec -(3600*h))/60;
            printf("Minute passed : %f \n",login_users[i].min);
            double payslip=login_users[i].min*(per_hour_cost/60);
            login_users[i].payment = payslip;
            printf("\n");
        }
    }
}

int totalSizeString(const char* str)
{
	char* c = &str[0];
	int size = 0;
	while(*c != '\0')
	{
		c++;
		size++;
	}
	return size;
}

void write_logged_in(int findpc)
{
    //struct history record;
    int fd = open("logged_in.txt", O_WRONLY | O_APPEND);
	int copy_desc = dup(fd);
	char tempArr[300];
	int tempSize;

    char findpc1[5];
    sprintf(findpc1, "%d", findpc);
    strcpy(tempArr, findpc1);
	strcat(tempArr, ", ");
    strcat(tempArr, login_users[findpc].username);
    strcat(tempArr, ", ");
    char day[5],month[5],year[5];
	sprintf(day, "%d", login_users[findpc].date.day);
	strcat(tempArr, day);
    strcat(tempArr, "/");
    sprintf(month, "%d", login_users[findpc].date.month);
	strcat(tempArr, month);
    strcat(tempArr, "/");
    sprintf(year, "%d", login_users[findpc].date.year);
	strcat(tempArr, year);
    strcat(tempArr, "/");
    strcat(tempArr, ", ");
    char snum[10];
    sprintf(snum, "%f", login_users[findpc].min);
    strcat(tempArr, snum);
    strcat(tempArr, ", ");
    char mnum[10];
    sprintf(mnum, "%f", login_users[findpc].payment);
    strcat(tempArr, mnum);

	write(copy_desc, "\n", 1);
	write(copy_desc, tempArr, totalSizeString(tempArr));
}

void * thread_login(void *arg)
{
    int  *findpc = arg;
    printf("\n pc no is :- %d and Thread ID is :- %u",*findpc,(unsigned int)pthread_self());
    login_users[*findpc].threadId = pthread_self();
    while(1)
    {
        if(out[login_users[*findpc].pcdet.pc_no]==1)
        {
            out[*findpc]=2;
            total_pc[*findpc].status=0;
            login_users[*findpc].logout=time(NULL);
            double sec = difftime(login_users[*findpc].logout,login_users[*findpc].login);
            double h = (sec/3600); 
            login_users[*findpc].min = (sec -(3600*h))/60;
            //printf("\n mins = %0.2f",login_users[*findpc].min);
            double payslip=login_users[*findpc].min*(per_hour_cost/60);
            login_users[*findpc].payment = payslip;
            write_logged_in(*findpc);
            printf("logout succesfull of %s from pc No. %d" ,login_users[*findpc].username ,*findpc);
            login_users[*findpc]=temp;
            pthread_exit((void *) findpc);
        }
    }
}



int login_newuser()
{
    char* username = malloc(100);
    printf("\nEnter Username : ");
    //printf("\nvatsal--------------1\n");
    scanf("%s",username);
    //printf("Logging %s" ,username);
    //finding pc whic is empty
    int findpc=0;
    while(out[findpc]!=2)
    {
        findpc++;
        if(findpc>9)
            break;
    }
    if(findpc>9)
    {
        printf("PC not available");
        return 0;
    }
    
    printf("Logging %s to Pc no %d" ,username ,findpc);

    out[findpc] = 0;
    total_pc[findpc].status = 1;
    login_users[findpc].username = malloc(100);
    strcpy(login_users[findpc].username,username);
    login_users[findpc].pcdet = total_pc[findpc];
    printf("Enter Day : ");
    scanf("%d",&login_users[findpc].date.day);
    printf("Enter Month : ");
    scanf("%d",&login_users[findpc].date.month);
    printf("Enter Year : ");
    scanf("%d",&login_users[findpc].date.year);
    login_users[findpc].payment=0;
    login_users[findpc].login=time(NULL);
    login_users[findpc].logout=time(NULL);
    login_users[findpc].min=0;
    //creating a thread
    printf("\n--------------------------------------------------------------%d\n",findpc);
    err = pthread_create (&threadID[findpc], NULL, thread_login, (void *)&findpc);
	if (err != 0)
	    printf("cant create thread: %s\n", strerror(err));
    free(username);
    return 1;
}

void logout_user()
{
    int l;
    printf("enter pc no to logout --------------\n");
    printf("\n----------------------------------------------2\n");
    scanf("%d",&l);
    out[l]=1;
           // out[l]=2;
            // printf("\n----------------------------------------------2\n");
            // total_pc[l].status=0;
            // login_users[l].logout=time(NULL);
            // double sec = difftime(login_users[l].logout,login_users[l].login);
            // double h = (sec/3600); 
            // login_users[l].min = (sec -(3600*h))/60;
            // //printf("\n mins = %0.2f",login_users[*findpc].min);
            // double payslip=login_users[l].min*(per_hour_cost/60);
            // login_users[l].payment = payslip;
            // write_logged_in(l);
            // printf("logout succesfull of %s from pc No. %d" ,login_users[l].username ,l);
            // login_users[l]=temp;
}