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
int main()
{
    FILE *fp = fopen("demo1.txt", "a+");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
   
	char line[300];
    
    int i=0;
    double newbal;
    char date[20];
    char uname[20];
	while (fgets(line, sizeof(line), fp))
	{
        
        char *token;
		token = strtok(line, ", ");
        strcpy(date, token);
        token = strtok(NULL, ", ");
        strcpy(uname, token);
        int a = ftell(fp);
        printf("%d",a);
        printf("vatsal shah1\n");
       if(strcmp("vatsal",uname)==0)
        {
            
            token = strtok(NULL, ", ");
            newbal = 300;
            char mnum[10];
            sprintf(mnum, "%f", newbal);
            printf("vatsal shah2\n");
            printf("%d\n",fseek(fp, a, SEEK_SET));
            fprintf(fp, "%s",mnum );
            break;
        }
    }
}