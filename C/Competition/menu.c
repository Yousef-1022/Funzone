#include "menu.h"
#include "primaryFunctions.h"
#include "secondaryFunctions.h"
#include "printFunctions.h"
#include "competition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//const char *Region[] = {"Bartfa", "Lovas", "Szula", "Kígyós-patak", "Malom telek", "Páskom", "Káposztás kert"};
const char *Region[] = {"Friend Tree", "Horse","Snake Creek", "Cabbage Garden", "Sula", "Mill Plot", "Pasture"};



int MenuPrint() {
    int choice;
    printf("\n****************************************\n");
    printf("0. Exit\n");
    printf("1. Adding an applicant into the list\n");
    printf("2. Adding applicants by region\n");
    printf("3. Remove an applicant from the list\n");
    printf("4. Print the list\n");
    printf("5. Print the list according to a certain region\n");
    printf("6. Modify the list\n");
    printf("7. Want to start the competition and get to see the results?\n");
    printf("****************************************\n");

    printf("Choose a number from the menu: ");
    scanf("%d", &choice);   //Leaves an end of line

    if (choice > 8 || choice < 0) return 8; //8 makes the user try again
    else return choice;
}



void AddIntoList() {

    char* BUFFER = malloc (1025);
    printf("\nPlease enter the name of the applicant: ");
    getchar();  fgets(BUFFER,1024,stdin);
    BUFFER[strcspn(BUFFER, "\n")] = 0; 

    
    FILE* fileName;
    fileName = fopen("list_ppl.txt","r");
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);
    fclose(fileName);

    if ( doesNameExistInFile(BUFFER,"list_ppl.txt") == 0  && (fileSize != 0) ) { printf("\nThe name: '%s' already exists in the list!\n",BUFFER); free (BUFFER); return; }

    printf("Choose one of the available regions: \n");
    for(int i=0; i<7; i++) printf("%d. %s\n",i+1,Region[i]); 

    printf("Choose region: ");
    int x;
    scanf("%d",&x);

    printf("Please enter the number of enteries: ");
    int Entry;
    scanf("%d",&Entry);

    if (x<1 || x>7 || Entry<=0) { printf("Please a valid number.\n"); free (BUFFER); }
    else {   
        char quickBuff [50];
        strcpy(quickBuff,Region[x-1]);

        char* Entry_asSTRING = malloc (1025);
        sprintf(Entry_asSTRING, "%d", Entry); 
        BUFFER[strcspn(BUFFER, "\n")] = 0;

        strcat(BUFFER,";"); strcat(BUFFER,quickBuff); strcat(BUFFER,";"); strcat(BUFFER,Entry_asSTRING);
        free(Entry_asSTRING);

        addIntoFile(BUFFER,"list_ppl.txt");
        free(BUFFER);
        printf("Success!\n");
    }

}



void AddByRegion () {

   printf("\nAvailable regions: \n");
   for(int i=0; i<7; i++) { printf("%d. %s\n",i+1,Region[i]); }

   printf("\nChoose region: ");
   int x; scanf("%d",&x); printf("\n");

   if (x<1 || x>7) printf("\nPlease put the correct number.\n");
   else {   
       char quickBuff [50];
       strcpy(quickBuff,Region[x-1]);

       char* BUFFER = malloc (1025);
        //------------------CheckAllocation---------------- 
        if (BUFFER == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { AddByRegion () function -> BUFFER couldn't be allocated! } - Exiting program!\n");
            exit (-1);    
        }
        //------------------CheckAllocation----------------

        printf("Write the amount of applicants: ");
        int y; scanf("%d",&y); printf("\n"); 
        getchar();

        FILE* fileName;
        fileName = fopen("list_ppl.txt","r");
        fseek (fileName, 0, SEEK_END);
        int fileSize = ftell(fileName);
        fclose(fileName);

        for (int i=1; i<=y; i++) {
            printf("Enter the name of the applicant #%d: ",i);
            fgets(BUFFER,1024,stdin);
            BUFFER[strcspn(BUFFER, "\n")] = 0;
    
            if ( doesNameExistInFile(BUFFER,"list_ppl.txt") == 0 && (fileSize != 0)) { printf("\nThe name: '%s' already exists in the list!\n",BUFFER); free (BUFFER); return; }

            if (fileSize == 0) {

                printf("Enter the amount of enteries: ");   int tmp;
                scanf("%d",&tmp); getchar();

                char* Entry_asSTRING = malloc (1025);
                sprintf(Entry_asSTRING, "%d", tmp); 

                strcat(BUFFER,";"); strcat(BUFFER,quickBuff); strcat(BUFFER,";"); strcat(BUFFER,Entry_asSTRING);
                addIntoFile(BUFFER,"list_ppl.txt");
                free(Entry_asSTRING);
            }
            else {
                
                printf("Enter the amount of enteries: ");   int tmp;
                scanf("%d",&tmp); getchar();

                char* Entry_asSTRING = malloc (1025);
                sprintf(Entry_asSTRING, "%d", tmp); 

                strcat(BUFFER,";"); strcat(BUFFER,quickBuff); strcat(BUFFER,";"); strcat(BUFFER,Entry_asSTRING);
                addIntoFile(BUFFER,"list_ppl.txt");
                free(Entry_asSTRING);
            }
        }
        free(BUFFER);
        printf("\nSuccess!\n");

    }
}



void RemoveFromList() {

    FILE* fileName;
    fileName = fopen("list_ppl.txt","r");
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);
    fclose(fileName);

    if (fileSize == 0) { printf("\nList is empty. Please add applicants first!\n"); return; }

    printf("\nPlease enter the name of the applicant you would like to remove: ");
    char* BUFFER = malloc (1025);
   
    getchar();  fgets(BUFFER,1024,stdin);
    BUFFER[strcspn(BUFFER, "\n")] = 0;
    removeFromFile (BUFFER, "list_ppl.txt");
    free(BUFFER);
    
}



void SeeList() { printf("\n"); printFile("list_ppl.txt"); }



void PrintListByRegion() { 

   FILE* fileName;
   fileName = fopen("list_ppl.txt","r");
   fseek (fileName, 0, SEEK_END);
   int fileSize = ftell(fileName);
   fclose(fileName);

   if (fileSize == 0) { printf("\nList is empty. Please add applicants first!\n"); return; }
   
   printf("\nAvailable regions: \n");
   for(int i=0; i<7; i++) { printf("%d. %s\n",i+1,Region[i]); }

   printf("Choose region: ");
   int x;
   scanf("%d",&x);
   printf("\n");

   if (x<1 || x>7) printf("\nPlease put the correct number.\n");
   else {   
       char quickBuff [50];
       strcpy(quickBuff,Region[x-1]);
       printBasedOnRegion(quickBuff,"list_ppl.txt");
   }

}



void ModifyList() {

    FILE* fileName;
    fileName = fopen("list_ppl.txt","r");
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);
    fclose(fileName);

    if (fileSize == 0) { printf("\nList is empty. Please add applicants first!\n"); return; }

    printf("\nWhat would you like to modify?\n");
    printf("1. The name of an applicant\n");
    printf("2. The region of an applicant\n");
    printf("3. The amount of enteries of an applicant\n");
    printf("Please choose a number: ");
    int x; scanf("%d",&x);

    if (x < 1 || x > 3) printf("That was not a valid number!\n");
    else {

        if (x==1) {

            char* nameBUFF = malloc (1025);
            char* toBUFF = malloc (1025);
            //------------------CheckAllocation---------------
            if (nameBUFF == NULL || toBUFF == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { ModifyList () function -> BUFF couldn't be allocated! } - Exiting program!\n");
            exit (-1);
            }
            //------------------CheckAllocation---------------    
            
            printf("Please enter the name of the applicant you would like to modify: ");
            getchar();  fgets(nameBUFF,1024,stdin); 
            nameBUFF[strcspn(nameBUFF, "\n")] = 0;

            if ( doesNameExistInFile(nameBUFF,"list_ppl.txt") != 0 ) { printf("\nThe name: '%s' does not exist in the list!\n",nameBUFF); free(nameBUFF); free(toBUFF); }
            else {
                printf("Please enter the new name: ");
                fgets(toBUFF,1024,stdin); 
                toBUFF[strcspn(toBUFF, "\n")] = 0;

                modifyNameOfApplicant(nameBUFF,toBUFF,"list_ppl.txt");
                printf("Success!\n");

                free(toBUFF);
                free(nameBUFF);
            }


        }

        else if (x==2) {

            char* nameBUFF = malloc (1025);
            char* regionBUFF = malloc (50);
            //------------------CheckAllocation---------------
            if (nameBUFF == NULL || regionBUFF == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { ModifyList () function -> BUFF couldn't be allocated! } - Exiting program!\n");
            exit (-1);
            }
            //------------------CheckAllocation---------------    

            printf("Please enter the name of the applicant you would like to modify: ");
            getchar();  fgets(nameBUFF,1024,stdin); 
            nameBUFF[strcspn(nameBUFF, "\n")] = 0;

            if ( doesNameExistInFile(nameBUFF,"list_ppl.txt") != 0 ) { printf("\nThe name: '%s' does not exist in the list!\n",nameBUFF); free(nameBUFF); free(regionBUFF); }
            else {

                printf("You can choose one of these regions: \n");
                for (int i = 0; i<7; i++) printf("%d. %s\n",i+1,Region[i]);
                printf("Your choice: ");
                int enterR; scanf("%d",&enterR);

                if (enterR < 1 || enterR > 7) { printf("\nThat was not a valid choice.\n"); free(nameBUFF); free(regionBUFF); }
                else {
                    strcpy(regionBUFF,Region[enterR-1]);
                    modifyRegionOfApplicant(nameBUFF,regionBUFF,"list_ppl.txt");
                    printf("Success!\n");

                    free(nameBUFF);
                    free(regionBUFF);
                }
            }
        }
        else {
            char* nameBUFF = malloc (1025);
            //------------------CheckAllocation---------------
            if (nameBUFF == NULL) { 
            printf("Memory allocation failed!\n");
            printf("Reason: { ModifyList () function -> BUFF couldn't be allocated! } - Exiting program!\n");
            exit (-1);
            }
            //------------------CheckAllocation---------------    

            printf("Please enter the name of the applicant you would like to modify: ");
            getchar();  fgets(nameBUFF,1024,stdin); 
            nameBUFF[strcspn(nameBUFF, "\n")] = 0;

            if ( doesNameExistInFile(nameBUFF,"list_ppl.txt") != 0 ) { printf("\nThe name: '%s' does not exist in the list!\n",nameBUFF); free(nameBUFF); }
            else {
                printf("Please enter the amount of enteries: ");
                int Entry; scanf("%d",&Entry);

                if (Entry < 0) { printf("That input is not valid!\n",nameBUFF); free(nameBUFF); }
                else {
                    modifyEntryOfApplicant(nameBUFF,Entry,"list_ppl.txt");
                    printf("Success!\n");
                    free (nameBUFF);
                }
            }

        }

    }

}

void Compete() {

    FILE* fileName;
    fileName = fopen("list_ppl.txt","r");
    fseek (fileName, 0, SEEK_END);
    int fileSize = ftell(fileName);
    fclose(fileName);

    if (fileSize == 0) { printf("\nList is empty. Please add applicants first!\n"); return; }

    makeItHappen();

    printf("Would you like to see proof?\n");
    printf("1.YES\n2.NO\n");
    int x;  scanf("%d",&x);

    if ( x == 1 ) {
        printf("First group:\n");
        printFile("child1_tmp.txt");
        printf("Second group:\n");
        printFile("child2_tmp.txt");
        remove("child1_tmp.txt");
        remove("child2_tmp.txt");
    } 
    else if (x == 2) {
        printf("Understood.\n");
        remove("child1_tmp.txt");
        remove("child2_tmp.txt");
    }
    else {
        printf("That was not an option!\n");
        remove("child1_tmp.txt");
        remove("child2_tmp.txt");
    }
}


void Run() {
    int value;
    do {
        value = MenuPrint();
        switch(value){
            case 1:
                AddIntoList();      
            break;

            case 2:
                AddByRegion();
            break;

            case 3:
                RemoveFromList();   
            break;

            case 4:
                SeeList();          
            break;

            case 5:
                PrintListByRegion();
            break;

            case 6:
                ModifyList();       
            break;
            
            case 7:
                Compete();
            break;

            case 8:
                printf("\nThe given input was not a number included in the options. Try again!\n");
            break;

            default:
                printf("\nProgram closed.\n");
            break;
        }
    } while( value != 0) ;
}