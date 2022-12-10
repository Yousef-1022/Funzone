#ifndef PRIMARYFUNCTIONS_H
#define PRIMARYFUNCTIONS_H

void modifyNameOfApplicant (char* theNameToModify, char* toName, char* theFile);
void modifyRegionOfApplicant (char* theNameOfApplicant, char* toRegion, char* theFile);
void modifyEntryOfApplicant (char* theNameOfApplicant, int toEntry, char* theFile); 
void removeFromFile (char* theName, char* theFile);
void addIntoFile (char* theString, char* theFile);

#endif 