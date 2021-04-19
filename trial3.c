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
}
