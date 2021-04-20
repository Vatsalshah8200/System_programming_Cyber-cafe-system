//read and write
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

 struct history
 {
     char username[50];
     double time;
     int cash;
 };
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
void writehistory()
{
	struct history record;
	strcpy(record.username,"nakul");
	record.time=5;
	record.cash=150;
    int fd = open("History.txt", O_WRONLY | O_APPEND);
	int copy_desc = dup(fd);
	char tempArr[300];
	int tempSize;

    strcpy(tempArr, record.username);
	strcat(tempArr, ", ");
 		char snum[5];
	sprintf(snum, "%0.0f", record.time);
	strcat(tempArr, snum);
	strcat(tempArr, ", ");
		char money[5];
	sprintf(money, "%d", record.cash);
	strcat(tempArr, money);
	write(copy_desc, "\n", 1);
	write(copy_desc, tempArr, totalSizeString(tempArr));
}
int main()
{
    FILE *fp = fopen("History.txt", "r");
    printf("Vatsal  ----------- 1\n");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return -1;
	}
    printf("Vatsal  ----------- 2\n");
	//parentPID = getpid();
	//printf("Parent : %d\n", parentPID);
	char line[300];

	while (fgets(line, sizeof(line), fp))
	{
        //printf("Vatsal  ----------- 3\n");
		//totalPOs++;
		//pipe(fd[totalPOs]);
		char *token;
		token = strtok(line, ", ");
        //printf("Vatsal  ----------- 4\n");
		struct history record;
		strcpy(record.username, token);
		printf("Name : %s\n", record.username);
        //printf("Vatsal  ----------- 5\n");

		token = strtok(NULL, ", ");
        record.time = strtod(token,NULL);
        //record.time = atod(token);
		//strcpy(childPO.area, token);
		printf("time : %0.2f\n", record.time);

		token = strtok(NULL, ", ");
        record.cash = strtol(token, NULL, 10);
		//childPO.areaCode = atoi(token);
		printf("Payment : %d\n", record.cash);

		//pos[totalPOs] = childPO;

		printf("\n");
	}
	writehistory();
}
