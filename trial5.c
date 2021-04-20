//find and replace
//space hatai devani badhi txt files mathi it will make things easy
//find word and replace whole line
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

/* Function declaration */
struct history
 {
     char username[50];
     double time;
     int cash;
 };
void replaceAll(char *str, const char *oldWord, const char *newWord);
char * findstring( char* word)
{
    FILE *fp = fopen("History.txt", "r");
    printf("Vatsal  ----------- 1\n");
	if (fp == NULL)
	{
		printf("Unable to open the file\n");
		return 0;
	}
    printf("Vatsal  ----------- 2\n");
	//parentPID = getpid();
	//printf("Parent : %d\n", parentPID);
	char line[300];
    struct history record[100];
    int i=0;
	while (fgets(line, sizeof(line), fp))
	{
        //printf("Vatsal  ----------- 3\n");
		//totalPOs++;
		//pipe(fd[totalPOs]);
		char *token;
		token = strtok(line, ", ");
        //printf("Vatsal  ----------- 4\n");
		
		strcpy(record[i].username, token);
		printf("Name : %s\n", record[i].username);
        //printf("Vatsal  ----------- 5\n");

		token = strtok(NULL, ", ");
        record[i].time = strtod(token,NULL);
        //record.time = atod(token);
		//strcpy(childPO.area, token);
		printf("time : %0.2f\n", record[i].time);

		token = strtok(NULL, ", ");
        record[i].cash = strtol(token, NULL, 10);
		//childPO.areaCode = atoi(token);
		printf("Payment : %d\n", record[i].cash);
        i++;
        printf("\n");
    }
    int j=i;
    i=0;
    printf("%s",word);
    //word="neel";
    for(i=0;i<j;i++)
    {
        printf("Name : %s\n", record[i].username);
        if(strcmp(record[i].username,word)==0)
            break;
    }
    // while(strcmp(record[i].username,word)!=0)
    // {
    //     i++;
    //     printf("Vatsal  ----------- 5\n");
    //     printf("%s\n",record[i].username);
    // }
    printf("Vatsal  ----------- 4\n");
    //i++;
    char* tempword=malloc(100);
    strcpy(tempword, record[i].username);
    strcat(tempword, ", ");
     
 		char snum[5];
	sprintf(snum, "%0.0f", record[i].time);
	strcat(tempword, snum);
	strcat(tempword, ", ");
		char money[5];
	sprintf(money, "%d", record[i].cash);
    
	strcat(tempword, money);
    
     printf("%s---------------------------------------------\n",tempword);
     printf("Vatsal  ----------- 6\n");
    return tempword;
}
int main()
{
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    int tempSize;
    char buffer[BUFFER_SIZE];
    char* oldWord1;
    char newWord[100],oldWord[100];


    printf("Enter path of source file: ");
    scanf("%s", path);

    getchar();
    printf("Enter word to replace: ");
    //fgets(oldWord1, 100, stdin);
    scanf("%s", oldWord1);
    strcpy(oldWord, findstring(oldWord1));
    //strcpy(oldWord, oldWord1);
    
    //use if entering string otherwis dont use
   // oldWord1[strlen(oldWord)-1] = '\0';
    getchar();
    printf("Replace word with: ");
   
    fgets(newWord, 100, stdin);
    //use if entering string otherwis dont use
    newWord[strlen(newWord)-1] = '\0';


    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
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


    /* Delete original source file */
    remove(path);

    /* Rename temp file as original file */
    rename("replace.tmp", path);

    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);

    return 0;
}



/**
 * Replace all occurrences of a given a word in string.
 */
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