#include "printFunctions.h"     //independent
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  printFile - printBasedOnRegion



void printFile (char* theFile) {
    
    FILE* fileName;
    fileName = fopen(theFile,"r");
    //------------------CheckFileOpen----------------
    if (fileName == NULL)    {  
        printf("File opening unsuccessful!\n");
        printf("Reason: { printFile () function -> fileName couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    //------------------CheckFileOpen----------------

    char* BUFFER = malloc (1025);
    //------------------CheckAllocation---------------- 
     if (BUFFER == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { printFile () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 

    while ( fgets (BUFFER,1024,fileName) ) {printf("%s",BUFFER); }

    free(BUFFER);
    fclose(fileName);
}



void printBasedOnRegion (char* theRegion, char* theFile) {

    FILE* fileName;
    fileName = fopen(theFile,"r");
    FILE* tmpFile;
    tmpFile = fopen("tmp_pFILE.txt","w");
    //------------------CheckFileOpen----------------
    if (tmpFile == NULL)    {    
        printf("File opening unsuccessful!\n");
        printf("Reason: { printBasedOnRegion () function -> tmpFile couldn't be opened! } - Exiting program!\n");
        exit (-1);      
    }
    if (fileName == NULL)    {  
        printf("File opening unsuccessful!\n");
        printf("Reason: { printBasedOnRegion () function -> fileName couldn't be opened! } - Exiting program!\n");
        exit (-1);        
    }
    //------------------CheckFileOpen----------------

        
    char* BUFFER = malloc (1025);
     //------------------CheckAllocation---------------- 
     if (BUFFER == NULL) { 
        printf("Memory allocation failed!\n");
        printf("Reason: { printBasedOnRegion () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
        exit (-1);    
    }
    //------------------CheckAllocation---------------- 
  
    BUFFER[0] = '\0';
    while ( fgets (BUFFER,1024,fileName) ) {
    
        int save1;  //Start of colon
        int save2;  //End of colon
        int simi=0; //For amount of similar characters
        int counter = 0;

        for(int i = 0; i<strlen(BUFFER); i++) { if (BUFFER[i] == ';') { save1=i+1; break; } }
        for(int i = save1; i<strlen(BUFFER); i++) { if (BUFFER[i] == ';') { save2=i; break; } }

        for(int i = save1; i<save2; i++) { 
            if (BUFFER[i] == theRegion[counter++]) simi++; 
            if( strlen(theRegion) < counter) break; 
        }

        int result = save2-save1;   //tmp var
        if ( (result == strlen(theRegion)) && (result == simi) ) {    //theRegion
            fprintf(tmpFile,BUFFER);
        }
        
    }

    free(BUFFER);
    fclose(fileName);
    fclose(tmpFile);

    tmpFile = fopen("tmp_pFILE.txt","r");
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);

    if (fileSize == 0) { printf ("Current list does not contain applicants from that region!\n"); fclose(tmpFile); remove("tmp_pFILE.txt"); }
    else { printFile("tmp_pFILE.txt"); fclose(tmpFile); remove("tmp_pFILE.txt"); }
    
}