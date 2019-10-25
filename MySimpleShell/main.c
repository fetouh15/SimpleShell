//

//  main.c

//  Simple Shell

//

//  Created by karim fathy on 10/17/18.

//  Copyright © 2018 Fetouh. All rights reserved.

//
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void createLogFile ()
{
    FILE *log;
    log=fopen("log","w");


    fclose(log);

}
signalHandler(int signal)
{
    FILE *log;
    log = fopen("log","a");


    fprintf(log,"%s","CHild process terminated\n");

    fclose(log);


}
int main(int argc, const char * argv[])
{

    createLogFile();

    signal(SIGCHLD,signalHandler);
    char command[100];

    char** commandline = (char **)calloc (20,sizeof(char*));

    while( 1 )

    {
        printf("Simple Shell ");

        gets(command);

        if(strcmp(command,"exit\n") == 0)

            break;
        if(strcmp(command,"\n") == 0)

            continue;

        int i=0;
        while(command[i]!='\n' && command[i]!=NULL )

        {
            i++;
        }

        command[i]=NULL; //tokenization
        char inst[10];

        i=0;

        commandline[0]= strtok(command," ");

        strcpy(inst,commandline[0]);



        while(commandline[i]!= NULL)

        {
            i++;

            commandline[i]=strtok(NULL," ");



        }



        pid_t pid= fork();
        int x=0;
        if(commandline[1]!= NULL)

        {
            x=strcmp(commandline[1],"&"); //if it is a background or foreground process
        }

        if(pid==0  )

        {
// if process is child


            if( x == 0 && commandline[1]!= NULL)
            {
                commandline[1]=NULL;
            }

            execvp(inst,commandline);

        }

        else

        {// if process is parent
            if( x!=0)

                wait(NULL);

        }


   delay(10000);  }

    exit(0);

    return 0;

}
