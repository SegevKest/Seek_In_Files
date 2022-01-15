#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MIN_NUM_OF_ARGS 3       // -- The min number of arguments - the first is the program name - we will not count it
#define TRUE 1      
#define FALSE 0


void returnNCharFromFile( const char * currFile, int indexToGet);

int checkForValidN(const char *number); // Function that is responsible for checking the validity of the N number received
int checkForValidArgs(int argc);    // Function that checks the valid amount of arguments.
int validateOpenedFile(FILE * currFile);    // function that validates if the opened file was a success
int getLengthOfFile(FILE * currFile);       // function that calculates the length of the content of the file
int validateFileLength(int fileLength, int indexToGet);     // file that validates if the file length is proper with the indexToGet received
void returnAsciiCharByLocation(FILE * currFile, int indexToGet);    // the method that returns the ascii code for the letter found


int main(int argc , char *argv[]){

    int i, numberToGet = 0,
        validInput = TRUE, validArgs= TRUE, validN = TRUE;

    validArgs = checkForValidArgs(argc);

    validN = checkForValidN(argv[1]);

    if( !validN || !validArgs )
        validInput = FALSE;

    if (validInput) {

        numberToGet = atoi(argv[1]);
        for( i=2; i<argc ; i++){
            returnNCharFromFile(argv[i], numberToGet);
            printf("\n");
        }
    }
    else
        exit(TRUE);         // if the input is not valid, we will stop the program
}

void returnNCharFromFile( const char * currFile, int indexToGet){

    int fileLength = 0;
    int validOpen = TRUE, validLengthOfFile = TRUE;
    char currChar;

    printf("File %s\n", currFile);

    FILE *fileToCheck = fopen(currFile, "r");

    // Error handling the Scenario of not existing file - problem with open it
    validOpen = validateOpenedFile(fileToCheck);

    // if the file could not open - finish this iteration on file
    if( validOpen)  {

        // Checks the length of the current text file
        fileLength = getLengthOfFile(fileToCheck) ; 
        // validate if the length of the current file is not too short
        validLengthOfFile = validateFileLength(fileLength, indexToGet); 
        
        if(validLengthOfFile)
           returnAsciiCharByLocation(fileToCheck, indexToGet); // prints the relevant ASCII value of the relevant char

    }
    fclose(fileToCheck);
}

int checkForValidN(const char *number){

    int flagValid = TRUE , i;

    for(i =0; i<strlen(number); i++){
        
        if (! isdigit(number[i]) )
            flagValid = FALSE;
    }

    if ( !flagValid )
        printf("The number entered for check is not valid\n");
 

    if(flagValid && atoi(number) <=0 ){
        printf("The number entered is not valid\n");
        flagValid = FALSE;
    }

    return flagValid;
}

int checkForValidArgs(int argc){

    if( argc < MIN_NUM_OF_ARGS)
    {
        printf("Not a valid number of arguments\n");
        return FALSE;
    }

    //Remove this log
    //printf("valid number of arguments\n");
    return TRUE;
}

int validateOpenedFile(FILE * currFile){
    if( currFile == NULL) {
        // Check for valid file opening
        printf("Error: Current file is not exist\n");
    }
    return currFile == NULL ? FALSE : TRUE;
}

int getLengthOfFile(FILE * currFile){
    
    fseek(currFile, 0, SEEK_END);
    //printf("File length:  %ld \n", ftell(currFile));

    return ftell(currFile); 
}

int validateFileLength(int fileLength, int indexToGet){

    if(fileLength < indexToGet)
        printf("Error : the length of the file is too short!\n");

    return fileLength < indexToGet ? FALSE : TRUE;
}

void returnAsciiCharByLocation(FILE * currFile, int indexToGet){

    fseek(currFile, (indexToGet -1) , SEEK_SET );
    printf("The ASCII Code of the %d char is: %d \n\n", indexToGet, fgetc(currFile));
}