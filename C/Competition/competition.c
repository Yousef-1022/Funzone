#include <stdlib.h> //exit,srand
#include <errno.h> //Error_Homie
#include <unistd.h> //Fork,Write,Read,Pipe
#include <string.h>
#include <sys/wait.h> //waitpid

#include <time.h> //fortime
#include <fcntl.h>  //fortime
#include <string.h> // for strncpy
#include <stdio.h>




int isRegionOne (char* TheLineOfFile) {

    if ( strcmp(TheLineOfFile,"Friend Tree") == 0 ) return 1;
    if ( strcmp(TheLineOfFile,"Horse") == 0 ) return 1;
    if ( strcmp(TheLineOfFile,"Snake Creek") == 0 ) return 1;
    if ( strcmp(TheLineOfFile,"Cabbage Garden") == 0 ) return 1;
    return 0;
}

void makeItHappen () {

    pid_t child1; int pipe1_child1[2]; int pipe2_child1[2];
    pid_t child2; int pipe1_child2[2]; int pipe2_child2[2];
    char BUFFER [201];

    if (pipe(pipe1_child1) == -1) { perror("pipe1_child1 did not happen!\n"); exit(-1); }
    if (pipe(pipe2_child1) == -1) { perror("pipe2_child1 did not happen!\n"); exit(-1); }
    if (pipe(pipe1_child2) == -1) { perror("pipe1_child2 did not happen!\n"); exit(-1); }
    if (pipe(pipe2_child2) == -1) { perror("pipe2_child2 did not happen!\n"); exit(-1); }


    char maxChild1_name [201];  int maxChild1_value;
    char maxChild2_name [201];  int maxChild2_value;

    
    child1 = fork();
    if (child1 < 0 ) { perror("Child1 couldn't be forked!\n"); exit(-1); }
    if (child1 > 0) {   //Parent is here!   

     //---------------------------------- SEND TO CHILD1 ----------------------------------// 
        FILE* fileName; fileName = fopen("list_ppl.txt","r");
        close(pipe1_child1[0]);     //Close reading end (WHEN SENDING TO CHILD1)
        while ( fgets (BUFFER,200,fileName) ) { BUFFER[strcspn(BUFFER, "\n")] = 0;  char theRegion [201];
            

            //Seperate name - region
            int start; int end; int semi = 0;
            for(int i = 0; i<strlen(BUFFER); i++) {
                if(BUFFER[i] == ';' && semi == 0) { start=i+1; semi=1; continue; } 
                if(semi == 1 && BUFFER[i] == ';') { end=i-1; break; } 
            }
            memcpy(theRegion,&BUFFER[start],(end-start)+1);
            theRegion[(end-start)+1] = '\0';
            char tmpNAME [201]; memcpy(tmpNAME,&BUFFER[0],start-1);
            tmpNAME[start-1] = '\0';
            //Seperate name - region


            if ( isRegionOne(theRegion) ) { write(pipe1_child1[1],tmpNAME,sizeof(tmpNAME)); }   //Pipe
        }   close(pipe1_child1[1]); 
     //---------------------------------- SEND TO CHILD1 ----------------------------------//  

        //char maxChild1_name [201]; 
        //int maxChild1_value; 
        char tmp [100]; //{tmp for str to int}
        FILE* child1_file; child1_file = fopen("child1_tmp.txt","w+");    //To prove correctness

     //---------------------------------- GET FROM CHILD1 ----------------------------------//  
        close(pipe2_child1[1]); //Close writing end (WHEN READING FROM CHILD1)

        read(pipe2_child1[0],maxChild1_name,sizeof(maxChild1_name));        //1st assumed max
        read(pipe2_child1[0],tmp,sizeof(tmp)); maxChild1_value = atoi(tmp); //1st assumed max
        fprintf(child1_file,maxChild1_name); fprintf(child1_file,";"); fprintf(child1_file,"%d",maxChild1_value); fprintf(child1_file,"\n");
       
        while ( read(pipe2_child1[0],BUFFER,sizeof(BUFFER)) ) {

            int inner_tmp;
            read(pipe2_child1[0],tmp,sizeof(tmp)); inner_tmp = atoi(tmp); 
            fprintf(child1_file,BUFFER); fprintf(child1_file,";"); fprintf(child1_file,"%d",inner_tmp); fprintf(child1_file,"\n");

            if( maxChild1_value < inner_tmp ) { strcpy(maxChild1_name,BUFFER); maxChild1_value = inner_tmp; }
        }   close(pipe2_child1[1]); fclose(child1_file);
     //---------------------------------- GET FROM CHILD1 ----------------------------------//





        child2=fork();
        if (child2 < 0 ) { perror("Child2 couldn't be forked!\n"); exit(-1); }
        if (child2 > 0) {   //Parent is here!   

         //---------------------------------- SEND TO CHILD2 ----------------------------------// 
            FILE* fileName; fileName = fopen("list_ppl.txt","r");
            close(pipe1_child2[0]);     //Close reading end (WHEN SENDING TO CHILD1)
            while ( fgets (BUFFER,200,fileName) ) { BUFFER[strcspn(BUFFER, "\n")] = 0;  char theRegion [201];


                //Seperate name - region
                int start; int end; int semi = 0;
                for(int i = 0; i<strlen(BUFFER); i++) {
                    if(BUFFER[i] == ';' && semi == 0) { start=i+1; semi=1; continue; } 
                    if(semi == 1 && BUFFER[i] == ';') { end=i-1; break; } 
                }
                memcpy(theRegion,&BUFFER[start],(end-start)+1);
                theRegion[(end-start)+1] = '\0';
                char tmpNAME [201]; memcpy(tmpNAME,&BUFFER[0],start-1);
                tmpNAME[start-1] = '\0';
                //Seperate name - region


                if ( !isRegionOne(theRegion) ) { write(pipe1_child2[1],tmpNAME,sizeof(tmpNAME)); }   //Pipe
            }   close(pipe1_child2[1]); 
         //---------------------------------- SEND TO CHILD2 ----------------------------------//

            //char maxChild2_name [201]; 
            //int maxChild2_value; 
            char tmp [100]; //{tmp for str to int}
            FILE* child2_file; child2_file = fopen("child2_tmp.txt","w+");    //To prove correctness

         //---------------------------------- GET FROM CHILD2 ----------------------------------//
            close(pipe2_child2[1]); //Close writing end (WHEN READING FROM CHILD1)

            read(pipe2_child2[0],maxChild2_name,sizeof(maxChild2_name));        //1st assumed max
            read(pipe2_child2[0],tmp,sizeof(tmp)); maxChild2_value = atoi(tmp); //1st assumed max
            fprintf(child2_file,maxChild2_name); fprintf(child2_file,";"); fprintf(child2_file,"%d",maxChild2_value); fprintf(child2_file,"\n");
       
            while ( read(pipe2_child2[0],BUFFER,sizeof(BUFFER)) ) {

                int inner_tmp;
                read(pipe2_child2[0],tmp,sizeof(tmp)); inner_tmp = atoi(tmp); 
                fprintf(child2_file,BUFFER); fprintf(child2_file,";"); fprintf(child2_file,"%d",inner_tmp); fprintf(child2_file,"\n");

                if( maxChild2_value < inner_tmp ) { strcpy(maxChild2_name,BUFFER); maxChild2_value = inner_tmp; }
            }   close(pipe2_child2[1]); fclose(child2_file);        
         //---------------------------------- GET FROM CHILD2 ----------------------------------//

        }
        else { //Child2 is here!
            
         //---------------------------------- CHILD2 GET AND SEND ----------------------------------// 
            close(pipe1_child2[1]); //Close writing end (WHEN READING FROM PARENT)
            close(pipe2_child2[0]); //Close reading end (WHEN SENDING  TO  PARENT)
            while ( read(pipe1_child2[0],BUFFER,sizeof(BUFFER)) ) {

                //Random gen
                int fd = open("/dev/urandom", O_RDONLY); size_t x; read(fd, &x, 4); fd=x%100;
                char fd_asString [100]; sprintf(fd_asString, "%d", fd);

                //Send name first then value
                write(pipe2_child2[1],BUFFER,sizeof(BUFFER));
                write(pipe2_child2[1],fd_asString,sizeof(fd_asString));

            }   close(pipe1_child2[0]); close(pipe2_child2[1]);
            exit(0);
         //---------------------------------- CHILD2 GET AND SEND ----------------------------------// 
        }


        //After both finish:
        if (maxChild1_value > maxChild2_value) { printf("The winner is: '%s' with a score of: %d\n",maxChild1_name,maxChild1_value); }
        else { printf("The winner is: '%s' with a score of: %d\n",maxChild2_name,maxChild2_value); }



    }
    else {  //Child1 is here!  

     //---------------------------------- CHILD1 GET AND SEND ----------------------------------// 
        close(pipe1_child1[1]); //Close writing end (WHEN READING FROM PARENT)
        close(pipe2_child1[0]); //Close reading end (WHEN SENDING  TO  PARENT)
        while ( read(pipe1_child1[0],BUFFER,sizeof(BUFFER)) ) {

            //Random gen
            int fd = open("/dev/urandom", O_RDONLY); size_t x; read(fd, &x, 4); fd=x%100;
            char fd_asString [100]; sprintf(fd_asString, "%d", fd);

            //Send name first then value
            write(pipe2_child1[1],BUFFER,sizeof(BUFFER));
            write(pipe2_child1[1],fd_asString,sizeof(fd_asString));
            
        }   close(pipe1_child1[0]); close(pipe2_child1[1]);
     //---------------------------------- CHILD1 GET AND SEND ----------------------------------// 
        exit(0);
    }
}