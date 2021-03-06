#include "config.h"


void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void getpcstatus()
{
    for(int i=0;i<10;i++)
    {
        printf("Computer Number :- %d\n",total_pc[i].pc_no);
        if(total_pc[i].status==0)
        {
            printf("Computer is switched OFF\n");
        }
        else
        {
            printf("Computer is Switched ON\n");
        }
    }
}

void changepcstatus()
{
    int pcno;
    char yn;
    printf("Enter computer Number to check status :-");
    scanf("%d",&pcno);
    clean_stdin();
    printf("\nstatus of This computer Number %d is :-  ",pcno);
    if(total_pc[pcno].status==0)
        {
            printf("switched OFF\n");
            printf("Would You like to Turn ON (y/n)?");
            scanf("%c",&yn);
            if(yn=='y')
            {
                total_pc[pcno].status=1;
                
                printf("switched ON succesfully");
            }
        }
        else
        {
            printf("Switched ON\n");
            printf("Would You like to Turn OFF (y/n)?");
            scanf("%c",&yn);
            if(yn=='y')
            {
                total_pc[pcno].status=0;
                printf("switched OFF succesfully");
            }
        }
}

void setcost()
{
    printf("Enter per hour Charge for using Computers :-  ");
    scanf("%lf",&per_hour_cost);
    
    printf("Per hour cost for using computers = %0.2f\n",per_hour_cost);
}

int intial_screen()
{
    printf("\e[1;1H\e[2J");
    sleep(4);
    int choice;
    printf("\n");
    printf("-----------------------------------------------\n");
    printf("|           1: NewLogin                       |\n");
    printf("|           2: Logout                         |\n");
    printf("|           3: Logged IN Users                |\n");
    printf("|           4: Set Per Hour Cost              |\n");
    printf("|           5: Logout All The Users           |\n");
    printf("|           6: Get pc Status                  |\n");
    printf("|           7: calculate Total Income         |\n");
    printf("|           8: Switch on/of PC                |\n");
    printf("|           9: Recharge prepaid               |\n");
    printf("-----------------------------------------------\n");
    printf("Enter your choice from 1 - 9 : ");
 
    scanf("%d",&choice);
    printf("\n");
    clean_stdin();
    return choice;
}


void Display_login_user()
{
    printf("\n");
    printf("-----------------------------------------------------------\n");
    for(int i=0;i<10;i++)
    {
        if(login_users[i].pcdet.status==1)
        {
            printf("pc No. : %d \n" ,login_users[i].pcdet.pc_no);
            printf("Username : %s \n",login_users[i].username);
            printf("ThreadId : %u \n",login_users[i].threadId);

            login_users[i].logout=time(NULL);
            double sec=difftime(login_users[i].logout,login_users[i].login);
            printf("sec passed : %f \n",sec);
            //double h = (sec/3600); 
            login_users[i].min = sec ;
            printf("Minute passed : %f \n",login_users[i].min);
            double payslip=login_users[i].min*(per_hour_cost/60);
            printf("Total Payable amount : %f \n",payslip);
            login_users[i].payment = payslip;
            printf("\n");
        }
    }
}

int totalSizeString( char* str)
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


char * findstring( char* word)
{
    FILE *fp = fopen("History.txt", "r");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
   
	char line[300];
    int i=0;
    struct history record[100];//////////////////////////////////////////////////////////////
	while (fgets(line, sizeof(line), fp))
	{
		char *token;
		token = strtok(line, ", ");
		
		strcpy(record[i].username, token);
		

		token = strtok(NULL, ", ");
        
        record[i].time = strtod(token,NULL);
        

		token = strtok(NULL, ", ");
        record[i].cash = strtod(token, NULL);

        i++;
        printf("\n");
    }

    
    int j=sizeof(record) / sizeof(record[0]);
    i=0;
    //printf("%s \n",word);
    for(i=0;i<j;i++)
    {
        if(strcmp(record[i].username,word)==0)
            break;
    }
    
    
    char* tempword=malloc(100);
    strcpy(tempword, record[i].username);
    strcat(tempword, ", ");
     
 		char snum[5];
	sprintf(snum, "%0.0f", record[i].time);
	strcat(tempword, snum);
	strcat(tempword, ", ");
		char money[5];
	sprintf(money, "%0.0f", record[i].cash);
    
	strcat(tempword, money);
    
      
    fclose(fp);
    return tempword;

    
}


char * makestringtoreplace(int findpc)
{
    
    double time;
    double totpayment;
    char* tempArr = malloc(100);
    
    
    ////remove
    FILE *fp = fopen("History.txt", "r");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
   
	char line[300];
    int i=0;
    struct history record[100];//////////////////////////////////////////////////////////////
	while (fgets(line, sizeof(line), fp))
	{
		char *token;
		token = strtok(line, ", ");
		
		strcpy(record[i].username, token);
		

		token = strtok(NULL, ", ");
        
        record[i].time = strtod(token,NULL);
        

		token = strtok(NULL, ", ");
        record[i].cash = strtod(token, NULL);
		
        i++;
        printf("\n");
    }
    ////////////////////////////////////



    int j=sizeof(record) / sizeof(record[0]);
    for(i=0;i<j;i++)
    {
        
        if(strcmp(record[i].username,login_users[findpc].username)==0)
            break;
    }

    time = record[i].time + login_users[findpc].min;
    totpayment = record[i].cash + login_users[findpc].payment;
    
    strcpy(tempArr, record[i].username);
   
    strcat(tempArr, ", ");
    char snum[10];
    sprintf(snum, "%0.0f", time);
    strcat(tempArr, snum);
    strcat(tempArr, ", ");
    char mnum[10];
    sprintf(mnum, "%0.0f", totpayment);
    strcat(tempArr, mnum);
    fclose(fp);
    return tempArr;

}

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}


void write_history(int findpc)
{
     
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    int tempSize;
    char buffer[BUFFER_SIZE];
    
    char* oldWord1 = malloc(100);
    char newWord[100],oldWord[100];
    
    if(check_username_exsist(login_users[findpc].username)==true)
    {   
        strcpy(oldWord1, login_users[findpc].username);
        
        strcpy(oldWord, findstring(oldWord1));
        
        strcpy(newWord,makestringtoreplace(findpc));

        fPtr  = fopen("History.txt", "r");
        fTemp = fopen("replace.tmp", "w"); 

        if (fPtr == NULL || fTemp == NULL)
        {
            /* Unable to open file hence exit */
            printf("\nUnable to open file.\n");
            printf("Please check whether file exists and you have read/write privilege.\n");
            exit(EXIT_SUCCESS);
        }

        while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
        {
            // Replace all occurrence of word from current line
            replaceAll(buffer, oldWord, newWord);

            // After replacing write it to temp file.
            fputs(buffer, fTemp);
        }


        /* Close all files to release resource */
        fclose(fPtr);
        fclose(fTemp);

        //char path[100] = "History.txt";
        /* Delete original source file */
        remove("History.txt");
        
        /* Rename temp file as original file */
        rename("replace.tmp", "History.txt");
        
        printf("\n history  Successfully replaced all occurrences of '%s' with '%s'.\n", oldWord, newWord);
        

    }
    //append
    else
    {
    int fd = open("History.txt", O_WRONLY | O_APPEND);
    int copy_desc = dup(fd);
	char tempArr[300];
	int tempSize;

    strcpy(tempArr, login_users[findpc].username);
    strcat(tempArr, ", ");
    char snum[10];
    sprintf(snum, "%0.0f", login_users[findpc].min);
    strcat(tempArr, snum);
    strcat(tempArr, ", ");
    char mnum[10];
    sprintf(mnum, "%0.0f", login_users[findpc].payment);
    strcat(tempArr, mnum);


    write(copy_desc, "\n", 1);
	write(copy_desc, tempArr, totalSizeString(tempArr));
    close(fd);
    }
    
    free(oldWord1);

}
void write_logged_in(int findpc)
{
    
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
    close(fd);
    
}


char * findstringprepaid(char * oldWord1)
{
    FILE *fp = fopen("prepaid.txt", "r");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}

    char line[300];
   
    int i=0;
    char* date = malloc(100);
    char username[20];
	while (fgets(line, sizeof(line), fp))
	{
        char *token;
		token = strtok(line, ", ");

        token = strtok(NULL, ", ");
        strcpy(date, token);
        
        if(strcmp(date,oldWord1)==0)
        {
            strcat(date, ", ");
            token = strtok(NULL, ", ");
            prepaid = strtod(token,NULL);
            strcat(date, token);

            break;
        }
    }
    fclose(fp);
    return date;
}

int check_prepaid_deduct(int findpc)
{
    FILE * fPtr;
    FILE * fTemp;
    int tempSize;
    char buffer[BUFFER_SIZE];
    char* oldWord1 = malloc(100);
    char newWord[100],oldWord[100];
    
    strcpy(oldWord1, login_users[findpc].username);
        
    strcpy(oldWord, findstringprepaid(oldWord1));//make it

    char pay[10];
	
    strcpy(newWord, login_users[findpc].username);
    strcat(newWord, ", ");
    double payment = prepaid - login_users[findpc].payment;
    sprintf(pay, "%0.0f", payment);
	strcat(newWord, pay);
    strcat(newWord, "\n");



        fPtr  = fopen("prepaid.txt", "r");
        fTemp = fopen("replace1.tmp", "w"); 
   
        if (fPtr == NULL || fTemp == NULL)
        {
            /* Unable to open file hence exit */
            printf("\nUnable to open file.\n");
            printf("Please check whether file exists and you have read/write privilege.\n");
            exit(EXIT_SUCCESS);
        }

        while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
        {
            // Replace all occurrence of word from current line
            replaceAll(buffer, oldWord, newWord);

            // After replacing write it to temp file.
            fputs(buffer, fTemp);
        }
    
     
        /* Close all files to release resource */
        fclose(fPtr);
        fclose(fTemp);

    // char path[100] = "prepaid.txt";
        /* Delete original source file */
        remove("prepaid.txt");
        
         
        /* Rename temp file as original file */
         rename("replace1.tmp", "prepaid.txt");
        
     
        printf("\nprepaid Successfully replaced all occurrences of '%s' with '%s'.\n", oldWord, newWord);
        free(oldWord1);

}
bool prepaiduser(char* username)
{
    FILE *fp = fopen("prepaid.txt", "r");
    if (fp == NULL)
        {
            printf("Unable to open the file\n");
            return 0;
        }
    char line[300],uname[20];

    while (fgets(line, sizeof(line), fp))
	{
		char *token;
		token = strtok(line, ", ");
		

		token = strtok(NULL, ", ");
        strcpy(uname,token);
        if(strcmp(uname,username)==0)
        {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void * thread_login(void *arg)
{
    struct  user *findpc1 = arg;
    int findpc = findpc1->pcdet.pc_no;
    printf("\n pc no is :- %d and Thread ID is :- %u",findpc,(unsigned int)pthread_self());
    login_users[findpc].threadId = pthread_self();
    while(1)
    {
        if(out[login_users[findpc].pcdet.pc_no]==1)
        {
            sleep(1);
            out[findpc]=2;
            total_pc[findpc].status=0;
            login_users[findpc].logout=time(NULL);
            double sec = difftime(login_users[findpc].logout,login_users[findpc].login);
            //double h = (sec/3600); 
            login_users[findpc].min = sec;
            
            double payslip=login_users[findpc].min*(per_hour_cost/60);
            login_users[findpc].payment = payslip;
            login_users[findpc].status=0;
           ////////////// pthread_mutex_lock(&mutexthread);
           pthread_rwlock_wrlock(&rw_lock);
            write_logged_in(findpc);
            
            write_history(findpc);
            
            if(prepaiduser(login_users[findpc].username)==true)
                check_prepaid_deduct(findpc);
            pthread_rwlock_unlock(&rw_lock);
            /////////////pthread_mutex_unlock(&mutexthread);
            printf("\nlogout succesfull of %s from pc No. %d\n" ,login_users[findpc].username ,findpc);
            login_users[findpc]=temp;
            break;
        }
    }
        pthread_exit((void *) findpc1);
}

bool check_username_exsist(char* username){
    FILE *fp = fopen("History.txt", "r");
    if (fp == NULL)
        {
            printf("Unable to open the file\n");
            return 0;
        }
    char line[300];
    struct history record;

    while (fgets(line, sizeof(line), fp))
	{
		char *token;
		token = strtok(line, ", ");
		strcpy(record.username, token);

		token = strtok(NULL, ", ");
        record.time = strtod(token,NULL);

		token = strtok(NULL, ", ");
        record.cash = strtol(token, NULL, 10);

        if(strcmp(record.username,username)==0)
        {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}


int login_newuser()
{
    char* username = malloc(100);
    char newusr;
    printf("Is It a New user(y/n)\n");
    scanf("%c",&newusr);

    printf("\nEnter Username : ");
    scanf("%s",username);
    if(newusr=='y')
    {
        while(check_username_exsist(username)==true)
        {
            free(username);
            username = malloc(100);
            printf("\nUsername already exsist\n Enter New Name : - ");
            scanf("%s",username);
        }
    }
    //finding pc which is empty
    
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
    
    printf("Logging in :-  %s, to Pc No. :- %d\n" ,username ,findpc);

    out[findpc] = 0;
    total_pc[findpc].status = 1;
    login_users[findpc].username = malloc(100);
    strcpy(login_users[findpc].username,username);
    login_users[findpc].status=1;
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
    //printf("\n--------------------------------------------------------------%d\n",findpc);
    err = pthread_create (&threadID[findpc], NULL, thread_login, (void *)&login_users[findpc]);
	if (err != 0)
	    printf("cant create thread: %s\n", strerror(err));
    free(username);
    return 1;
}

double searchIncomeByDate(char* date)
{
    FILE *fp = fopen("logged_in.txt", "r");
    if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
    char line[300];
    double total;
    char newdate[20];
    while (fgets(line, sizeof(line), fp))
	{
	    char *token;
		token = strtok(line, ", ");
        //pcno
        token = strtok(NULL, ", ");
        //name
        token = strtok(NULL, ", ");
        strcpy(newdate, token);
        if(strcmp(newdate,date)==0)
        {
            token = strtok(NULL, ", ");
            //min
            token = strtok(NULL, ", ");
            total = total + strtod(token,NULL);
        }

    }
    fclose(fp);
    return total;
}
bool prepaiduserexsist(char* username)
{
    FILE *fp = fopen("prepaid.txt", "r");
    if (fp == NULL)
        {
            printf("Unable to open the file\n");
            return 0;
        }
    char line[300];
    char uname[20];

    while (fgets(line, sizeof(line), fp))
	{
		char *token;
		token = strtok(line, ", ");

		token = strtok(NULL, ", ");
        strcpy(uname,token);

        if(strcmp(uname,username)==0)
        {
            char newWord[100],oldWord[100];
            //FILE * fPtr;
            FILE * fTemp;
            int tempSize;
            char buffer[BUFFER_SIZE];
            double plans,addbal;

            strcpy(oldWord,username);
            strcat(oldWord, ", ");
            token = strtok(NULL, ", ");
            plans = strtod(token,NULL);
            strcat(oldWord, token);

            printf("Add amount to Add : - ");
            scanf("%lf",&addbal);
            plans=plans+addbal;
            
            strcpy(newWord,username);
            strcat(newWord, ", ");
            char snum[5];
	        sprintf(snum, "%0.0f", plans);
            strcat(newWord, snum);
            
            
            fseek( fp, 0, SEEK_SET );
            
            fTemp = fopen("replace3.tmp", "w");
             if ( fTemp == NULL)
            {
                /* Unable to open file hence exit */
                printf("\nUnable to open file.\n");
                printf("Please check whether file exists and you have read/write privilege.\n");
                exit(EXIT_SUCCESS);
            }

            while ((fgets(buffer, BUFFER_SIZE, fp)) != NULL)
            {
                // Replace all occurrence of word from current line
                replaceAll(buffer, oldWord, newWord);

                // After replacing write it to temp file.
                fputs(buffer, fTemp);
            }
            
            fclose(fp);
            fclose(fTemp);
            
            remove("prepaid.txt");
            rename("replace3.tmp", "prepaid.txt");
            
            return true;
        }
    }
    fclose(fp);
    return false;
}




void prepaidplan()
{
        char username[100];
        printf("Enter Username: - ");
        scanf("%s",username);
    if( prepaiduserexsist(username) == false)
    {
        //int fd = open("prepaid.txt", O_WRONLY | O_APPEND);
        FILE *fp = fopen("prepaid.txt", "a");
        //int copy_desc = dup(fd);
        char tempArr[300];
        int tempSize;

    strcpy(tempArr,"\n");
        char day[5],month[5],year[5];
        printf("Enter Day: - ");
        scanf("%s",day);
        strcat(tempArr, day);
        strcat(tempArr, "/");
        
        printf("Enter Month: - ");
        scanf("%s",month);
        strcat(tempArr, month);
        strcat(tempArr, "/");
        printf("Enter Year: - ");
        scanf("%s",year);
        strcat(tempArr, year);
        strcat(tempArr, ", ");

        
        strcat(tempArr,username);
        strcat(tempArr, ", ");
        
        char mnum[10];
        printf("Enter Balance: - ");
        scanf("%s",mnum);
        strcat(tempArr, mnum);

        fputs(tempArr,fp);
        fclose(fp);
        // write(copy_desc, "\n", 1);
        // write(copy_desc, tempArr, totalSizeString(tempArr));
        //close(fd);
    }
    else
    {
        printf("Username Balance Updated");
    }
}


double searchIncomeByUname(char* uname)
{
    FILE *fp = fopen("History.txt", "r");
    if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
    char line[300];
    double total;
    char name[20];
    while (fgets(line, sizeof(line), fp))
	{
        char *token;
		token = strtok(line, ", ");
        strcpy(name, token);
        if(strcmp(name,uname)==0)
        {
            token = strtok(NULL, ", ");
            //time
            token = strtok(NULL, ", ");
            total = strtod(token,NULL);
            break;
        }

    }
    fclose(fp);
    return total;
}

void getincome()
{
    char ch;
    printf("d :- for date wise income  and \nu :- for user wise income\n");
    scanf("%c",&ch);
    if(ch=='d')
    {
        char date[100];
        double in;
        printf("Enter date to calculate income : - ");
        scanf("%s",date);
        in =  searchIncomeByDate(date);
        printf("Total income on %s is %f",date ,in);

    }
    else if(ch=='u')
    {
        char uname[100];
        double in;
        printf("Enter username to calculate income : - ");
        scanf("%s",uname);
        in =  searchIncomeByUname(uname);
        printf("Total income From User %s is %f",uname ,in);

    }
}



void logout_user()
{
    int l;
    printf("enter pc no to logout : -");
    scanf("%d",&l);
    out[l]=1;
}

void logoutall()
{
    for(int i=0;i<10;i++)
    {
        if(login_users[i].status==1)
        {
            out[i]=1;
        }
    }
}