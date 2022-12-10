#include "primaryFunctions.h"
#include "secondaryFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  modifyNameOfApplicant - modifyRegionOfApplicant - modifyEntryOfApplicant - removeFromFile - addIntoFile



void modifyNameOfApplicant (char* theNameToModify, char* toName, char* theFile) {

    FILE* orgFile;
    orgFile = fopen(theFile,"r");
    FILE* tmpFile;
    tmpFile = fopen("tmp_mFILE.txt","w");
    //------------------CheckFileOpen----------------
    if (tmpFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyNameOfApplicant () function -> tmpFile couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    if (orgFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyNameOfApplicant () function -> orgFile couldn't be opened! } - Exiting program!\n");
        exit (-1);        
    }
    //------------------CheckFileOpen----------------


    char* BUFFER = malloc (1025);
    //------------------CheckAllocation---------------- 
     if (BUFFER == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { modifyNameOfApplicant () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    while ( fgets (BUFFER,1024,orgFile) ) {
        
        //--GetName (quickTmp)
        char* quickTmp = malloc (1025);
    //------------------CheckAllocation---------------- 
    if (quickTmp == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { modifyNameOfApplicant () function -> quickTmp couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //-----------------CheckAllocation---------------- 


        for(int i = 0; i<strlen(BUFFER); i++) {
            if ( BUFFER[i] == ';') { quickTmp[i] = '\0'; break; }   //Important!
            quickTmp[i] = BUFFER[i];
        }
        //--GetName

        if ( strcmp(quickTmp,theNameToModify) == 0 ) changeName(BUFFER,toName);
        fprintf(tmpFile,BUFFER);
        free (quickTmp);
    }

    free(BUFFER);
    fclose(orgFile);
    remove(theFile);
    rename("tmp_mFILE.txt",theFile);
    fclose(tmpFile);
}



void modifyRegionOfApplicant (char* theNameOfApplicant, char* toRegion, char* theFile) {

    FILE* orgFile;
    orgFile = fopen(theFile,"r");
    FILE* tmpFile;
    tmpFile = fopen("tmp_mFILE.txt","w");
    //------------------CheckFileOpen----------------
    if (tmpFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyRegionOfApplicant () function -> tmpFile couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    if (orgFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyRegionOfApplicant () function -> orgFile couldn't be opened! } - Exiting program!\n");
        exit (-1);        
    }
    //------------------CheckFileOpen----------------


    char* BUFFER = malloc (1025);
    //------------------CheckAllocation---------------- 
    if (BUFFER == NULL) { 
       printf("Memory allocation failed!\n");
       printf("Reason: { modifyRegionOfApplicant () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
       exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    while ( fgets (BUFFER,1024,orgFile) ) {
        
        //--GetName (quickTmp)
        char* quickTmp = malloc (1025);
        //------------------CheckAllocation---------------- 
        if (quickTmp == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { modifyRegionOfApplicant () function -> quickTmp couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        }
        //------------------CheckAllocation---------------- 


        for(int i = 0; i<strlen(BUFFER); i++) {
            if ( BUFFER[i] == ';') { quickTmp[i] = '\0'; break; }   //Important!
            quickTmp[i] = BUFFER[i];
        }
        //--GetName

        if ( strcmp(quickTmp,theNameOfApplicant) == 0 ) changeRegion(BUFFER,toRegion);
        fprintf(tmpFile,BUFFER);
        free (quickTmp);
    }

    free(BUFFER);
    fclose(orgFile);
    remove(theFile);
    rename("tmp_mFILE.txt",theFile);
    fclose(tmpFile);
}



void modifyEntryOfApplicant (char* theNameOfApplicant, int toEntry, char* theFile) {

    FILE* orgFile;
    orgFile = fopen(theFile,"r");
    FILE* tmpFile;
    tmpFile = fopen("tmp_mFILE.txt","w");
    //------------------CheckFileOpen----------------
    if (tmpFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyEntryOfApplicant () function -> tmpFile couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    if (orgFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { modifyEntryOfApplicant () function -> orgFile couldn't be opened! } - Exiting program!\n");
        exit (-1);        
    }
    //------------------CheckFileOpen----------------


    char* BUFFER = malloc (1025);
    //------------------CheckAllocation---------------- 
    if (BUFFER == NULL) { 
       printf("Memory allocation failed!\n");
       printf("Reason: { modifyEntryOfApplicant () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
       exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    while ( fgets (BUFFER,1024,orgFile) ) {
        
        //--GetName (quickTmp)
        char* quickTmp = malloc (1025);
        //------------------CheckAllocation---------------- 
        if (quickTmp == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { modifyEntryOfApplicant () function -> quickTmp couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        }
        //------------------CheckAllocation---------------- 


        for(int i = 0; i<strlen(BUFFER); i++) {
            if ( BUFFER[i] == ';') { quickTmp[i] = '\0'; break; }   //Important!
            quickTmp[i] = BUFFER[i];
        }
        //--GetName

        if ( strcmp(quickTmp,theNameOfApplicant) == 0 ) { 
            changeEntry(BUFFER,toEntry); 
            fprintf(tmpFile,BUFFER);
            fprintf(tmpFile,"\n"); 
            free (quickTmp);
        }
        else {
        fprintf(tmpFile,BUFFER);
        free (quickTmp);
        }

    }

    free(BUFFER);
    fclose(orgFile);
    remove(theFile);
    rename("tmp_mFILE.txt",theFile);
    fclose(tmpFile);
}



void removeFromFile (char* theName, char* theFile) {

    if ( doesNameExistInFile (theName,theFile) != 0 ) printf("\nThis applicant: '%s' does not exist in the list!\n",theName);
    else {

        FILE* tmpFile;
	    tmpFile = fopen("tmp_FILE.txt","w");
        FILE* orgFile ;
	    orgFile = fopen(theFile,"r");

        //------------------CheckFileOpen----------------
        if (tmpFile == NULL)    {  
            printf("File opening unsuccessful!\n");
            printf("Reason: { removeFromFile () function -> tmpFile couldn't be opened! } - Exiting program!\n");
            exit (-1);      
        }
        if (orgFile == NULL)    {    
            printf("File opening unsuccessful!\n");
            printf("Reason: { removeFromFile () function -> orgFile couldn't be opened! } - Exiting program!\n");
            exit (-1);        
        }
        //------------------CheckFileOpen----------------


        char* BUFFER = malloc (1025);
        //------------------CheckAllocation---------------- 
        if (BUFFER == NULL) {   //Checking if memory allocation worked.
            printf("Memory allocation failed!\n");
            printf("Reason: { removeFromFile () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        } 
        //------------------CheckAllocation----------------
        


        while ( fgets(BUFFER,1024,orgFile) ) {
            
            int x;
            for (int i = 0; i<strlen(BUFFER); i++) {
                if (BUFFER[i] == ';') break;
                x = i+1;
            }

            char* nameFromLine = malloc(x+1);
            //------------------CheckAllocation---------------- 
            if (nameFromLine == NULL) {  
                printf("Memory allocation failed!\n"); 
                printf("Reason: { removeFromFile () function -> nameFromLine couldn't be allocated! } - Exiting program!\n");
                exit (-1);    
            }
            //------------------CheckAllocation---------------- 

            strncpy(nameFromLine, BUFFER, x);
            nameFromLine[x+1] = '\0';
            
            if ( strcmp(theName,nameFromLine) != 0) fprintf(tmpFile,BUFFER);
            free (nameFromLine); 

        }

        
        free (BUFFER);
        fclose(orgFile);
        remove(theFile);

        rename("tmp_FILE.txt",theFile);
        fclose(tmpFile);
        printf("Success!\n");
    }

}



void addIntoFile (char* theString, char* theFile) {

    int x;
    for (int i = 0; i<strlen(theString); i++) {
        if (theString[i] == ';') break;
        x = i+1;
    }


    char* theName = malloc(x+1);
    //------------------CheckAllocation---------------- 
    if (theName == NULL) {
        printf("Memory allocation failed!\n");
        printf("Reason: { addIntoFile () function -> theName couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 


    strncpy(theName, theString, x);
    theName[x+1] = '\0';

    int check = doesNameExistInFile(theName,theFile);

    FILE* fileName;
	fileName = fopen(theFile,"a+");
    //------------------CheckFileOpen----------------
    if (fileName == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { addIntoFile () function -> fileName couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    //------------------CheckFileOpen----------------

    //IF THE FILE IS EMPTY:
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);

    if ( check != 0 || fileSize == 0 )  {
        
        char* tmp = malloc (1025);
        //------------------CheckAllocation---------------- 
        if (tmp == NULL) {   
            printf("Memory allocation failed!\n");
            printf("Reason: { addIntoFile () function -> tmp couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        }
        //------------------CheckAllocation---------------- 


        strcpy(tmp,theString);
        strcat(tmp,"\n");

        fprintf( fileName,tmp);

        free(tmp);
        fclose(fileName);
    }
    else printf("The applicant: %s exists in the list!\n",theName);
        
    free(theName);
}