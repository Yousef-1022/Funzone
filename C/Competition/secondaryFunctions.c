#include "secondaryFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  doesNameExistInFile - changeName - changeRegion - changeEntry



int doesNameExistInFile (char* theName, char* theFile) {    //Returns 0 if exists

    FILE* fileName ;
	fileName = fopen(theFile,"r");
    //------------------CheckFileOpen----------------
    if (fileName == NULL)    {
        printf("File opening unsuccessful!\n");
        printf("Reason: { doesNameExistInFile () function -> fileName couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    //------------------CheckFileOpen----------------


    int answer = 0; // if not exist
    char* BUFFER = malloc (1025);
    //------------------CheckAllocation----------------
    if (BUFFER == NULL) {   
        printf("Memory allocation failed!\n");
        printf("Reason: { doesNameExistInFile () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 


    while ( fgets(BUFFER,1024,fileName) )
    {
        int x;
        for (int i = 0; i<strlen(BUFFER); i++) {
            if (BUFFER[i] == ';') break;
            x = i+1;
        }


        char* substr = malloc(x+1);
        //------------------CheckAllocation---------------- 
        if (substr == NULL) {   
            printf("Memory allocation failed!\n");
            printf("Reason: { doesNameExistInFile () function -> substr couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        } 
        //------------------CheckAllocation---------------- 



        strncpy(substr, BUFFER, x);
        substr[x+1] = '\0';

        answer = strcmp(substr,theName);
        free (substr);

        if( answer == 0) break;

    }

    free(BUFFER);
    fclose(fileName);
    return answer;
}



void changeName (char* theLine, char* toName ) {    //Changes the Name of the line

    int stop; int counter = 0;      //theRest ( to get all the characters after the name including ; )
                                    //It uses counter as its own i , and stops when it hits the ; 

    char* theRest = malloc(1025); 
    //------------------CheckAllocation---------------- 
    if (theRest == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { changeName () function -> theRest couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    } 
    //------------------CheckAllocation---------------- 

    for (int i = 0; i<strlen(theLine); i++) {
        if (theLine[i] == ';') stop = 1; 
        if (stop == 1) theRest[counter++] = theLine[i];
    }

    char* theAns = malloc (1025);
    //------------------CheckAllocation---------------- 
    if (theAns == NULL) {  
        printf("Memory allocation failed!\n");
        printf("Reason: { changeName () function -> theAns couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation----------------  

    strcat(theAns,toName); strcat(theAns,theRest);  //concatenating
    strcpy(theLine,theAns);     //changing the value

    free (theAns);
    free (theRest);

}



void changeRegion (char* theLine, char* theRegion) {    //Changes the Region of the line

    int stop = 0;

    char* theStart = malloc(1025);      //To grab the info before the first ;
    //------------------CheckAllocation---------------- 
    if (theStart == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { changeRegion () function -> theStart couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    char* theEnd = malloc(1025);    int counter=0;      //To grab the info after the second ;
    //------------------CheckAllocation---------------- 
    if (theEnd == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { changeName () function -> theEnd couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 


    for (int i = 0; i<strlen(theLine); i++) {
        if (stop < 1) theStart[i] = theLine[i]; 
        if (theLine[i] == ';') stop++; 
        if (stop >= 2) theEnd[counter++] = theLine[i];
    }
    
    strcat(theStart,theRegion);    
    strcat(theStart,theEnd);   
    strcpy(theLine,theStart);
    
    free (theStart);
    free (theEnd);
}



void changeEntry (char* theLine, int toEntry) { //Changes the Entry of the line

    int stop = 0;       //If it is 2 it will get triggered and automatically finds the entry

    char* theAns = malloc(1025);    //Used to get the information before the entry
    //------------------CheckAllocation---------------- 
    if (theAns == NULL) {
        printf("Memory allocation failed!\n");
        printf("Reason: { changeEntry () function -> theAns couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    
    for (int i = 0; i<strlen(theLine); i++) {
        if (stop < 2) theAns[i] = theLine[i];
        if (theLine[i] == ';') stop++; 
    }


    char* toEntry_asSTRING = malloc (1025);     //This is here to change the entry to string 
    //------------------CheckAllocation---------------- 
    if (toEntry_asSTRING == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { changeEntry () function -> toEntry_asSTRING couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    sprintf(toEntry_asSTRING, "%d", toEntry);   //This is here inorder to concatenate

    strcat(theAns,toEntry_asSTRING);    //concatenating
    strcpy(theLine,theAns);   //changing the value

    free (theAns);
    free (toEntry_asSTRING);

}