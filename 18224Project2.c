/*************************************************************************************************************************************************
*                                                                                                                                                *
*                                      CO222 PROJECT 2 - MEETING DATA VISUALIZER - SPECIFICATION                                                 *
*                                                                                                                                                *
*                                            ARTHUR             :-  G.D RAVINDU MIHIRANGA                                                        *
*                                                                   E/18/224                                                                     *
*                                                                                                                                                *
*                                            LAST MODIFIED ON   :-  02/10/2021                                                                   *
*                                                                                                                                                *
*************************************************************************************************************************************************/

// Calling all the essential header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/************************************************************** STRUCTURES **********************************************************************/
// Structure for the data to be stored in a linked list data structure
// Here I have designed the structure to store those 3 values according to the user preference
// It won't store all the three types of data (number of meetings,participants number,time) at once
// If user enters '-p' then it will store only the participants number it won't store the time duration and number of meetings
typedef struct fileData{
    char fullName[40];           // Host Name
    long long mtpData;           // Data to be stored according to the given parameter
    struct fileData *next;       // structure reference of the next entry according to the alphabetic order
    struct fileData *arrNxt;     // structure reference of the next entry
} data;

// Structure to hold the file names using a linked link data structure
typedef struct fileNames{
    char fileName[30];           // string array to store file name
    struct fileNames *next;      // structure reference of the next file
} files;

/******************************************************* FUNCTION PROTOTYPES *******************************************************************/
long long timeConverter(char timeArr[]);
int rowsInputChecker(char str[]);
int csvChecker(char fileName[]);
int addData(char fileName[], char c);
int numberLength(long long num);
int maxStringLen(long long lines);
void sort(long long lines);
void plotData(long long lines,int scld);

/********************************************************* GLOBAL VARIABLES ********************************************************************/
// Global pointer array to store the nodes according to the alphabetic order and a slot to store non alphabet characters
data *nodes[27];
// Global pointer of a head to store the sorted data
data *stdHead = NULL;
// Declaring the global pointer variables of the two structures
files *fileHeader = NULL;
// Global integer to count the total number of entries
long long totalEntries =0;
// Global integer to calculate the total of the given type of data
long long totalData =0;
// Global integer variable to store the head of the linked list
int headCharValue = 0;
// Global variable to detect the the head of the structure
int headDetect = 0;

/************************************************************* FUNCTIONS ************************************************************************/

// Function to plot the data according to the given conditions
// Parameters :- number of rows to be shown in the graph, graph to be scaled or not
void plotData(long long lines, int scld){ /******************************************************************************************************/

    // Declaring variables
    data *current;
    long long i,j;
    float barSize;
    int maxNumLength, maxNameLength ,spaces, k, length;

    if (lines > totalEntries) lines = totalEntries;    // Checking whether the number of lines to be print will exceed the total entries
    maxNumLength = numberLength(stdHead ->mtpData);    // Getting the length of the lengthiest number
    maxNameLength = maxStringLen(lines);               // Getting the length of the lengthiest host name

    printf("\n");

    current = stdHead;                                 // Initializing the current data type pointer variable to the first node of the structure

    for (i=0;i<lines;++i){                             // Outer loop to iterate through the entry lines

        // Bar Size in the non scaled scenario
        if (scld == 0) barSize = (((float) current ->mtpData)*(77 - maxNameLength - maxNumLength))/ totalData;
        // Bar Size in the scaled scenario
        if (scld == 1) barSize = (((float) (77 - maxNameLength - maxNumLength))*(current ->mtpData))/ stdHead->mtpData;

        for (j=0;j<4;++j){                             // Inner loop to iterate through the print lines of a given entry

            // Printing the middle line of given entry
            if (j == 1){
                // Spaces to be print
                spaces = spaces - (strlen(current ->fullName) + 1);
                printf(" %s",current ->fullName);      // Printing the Host name
                // Printing the spaces
                for (k=0;k<spaces;++k){
                    printf(" ");
                }
                printf("\u2502");                      // Printing the vertical line
                // Printing the bar
                for (k=0;k<(int)barSize;++k){
                    printf("\u2591");
                }
                printf("%lld\n",current ->mtpData);    // Printing the value of the given type

            // Printing the 1st and 3rd lines in a given entry
            } else if ((j==0) || (j==2)){
                spaces = maxNameLength + 2;
                // Printing the spaces
                for (k=0;k<spaces;++k){
                    printf(" ");
                }
                printf("\u2502");                      // Printing the vertical line
                // Printing the bar
                for (k=0;k<(int)barSize;++k){
                    printf("\u2591");
                }
                printf("\n");

            // Printing the bottom line in a given entry
            } else {
                spaces = maxNameLength + 2;
                // Printing the spaces
                for (k=0;k<spaces;++k){
                    printf(" ");
                }
                printf("\u2502");                      // Printing the vertical line
                printf("\n");
            }
        }
        current = current ->next;                      // jumping to the next node of the structure
    }

    // Printing the spaces
    for (k=0;k<spaces;++k){
        printf(" ");
    }
    printf("\u2514");                                  // Printing the origin
    length = 80 - (maxNameLength+3);
    // Printing the horizontal line
    for (k=0;k<length;++k){
        printf("\u2500");
    }
    printf("\n");
}

// Function to calculate the number of digits in a number
int numberLength(long long num){ /**************************************************************************************************************/
    // Declaring variables
    char temp[30];
    int digits;
    // Using "sprintf" function to return the number of digits
    digits = sprintf(temp, "%lld",num);
    return digits;
}

// Function to calculate the length of the lengthiest name in the data structure up to a certain point
int maxStringLen(long long lines){ /**************************************************************************************************************/
    // Declaring variables
    long long i=0;
    int len = 0;
    data *current;
    current = stdHead;
    // Iterating through a loop to calculate the length
    while (i<lines){
        // Calculating the string length using "strlen" function
        if (len < strlen(current ->fullName)) len = strlen(current ->fullName);
        current = current ->next;
        ++i;
    }
    return len;
}
// Function to sort the data up to the given point
// finally the sorted values will store in another structure which is having all the sorted data
void sort(long long lines){ /***********************************************************************************************************************************/
    // Declaring Variables
    data *current1, *current2, *prevNode, *dataNode, *temp, *linkNode;
    long long maxVal, iter =0;

    // Changing the rows number if it is greater than the total entries
    if (lines > totalEntries) lines = totalEntries;

    // Iterating through the loop to select the largest first n numbers (n = number of rows to plot)
    while (iter < lines){                               // Iteration will stop when counter variables reaches rows number
        current1 = nodes[headCharValue];                // Initializing the nodes to the head of the structure
        current2 = nodes[headCharValue];                // and initializing the max value to -9999 every time when loop starts to iterate
        dataNode = NULL;
        prevNode = NULL;
        maxVal = -9999;

        while (current1 != NULL){                       // Iterating through the nodes to detect the largest value

            if (current1 ->mtpData > maxVal){
                maxVal = current1 ->mtpData;            // updating the maxVal variable
                dataNode = current1;                    // have a memory of the node to be deleted from the data structure
                prevNode = current2;                    // and it's previous node to connect the deleting node's next node
            }
            current2 = current1;                        // Updating the two counter nodes
            current1 = current1 ->arrNxt;               // to go through the structure nodes
        }

        // If the deleting node is the head of the structure
        if (dataNode == prevNode){
            nodes[headCharValue] = nodes[headCharValue] ->arrNxt;    // Updating the links between nodes
        } else{
            prevNode ->arrNxt = dataNode ->arrNxt;                   // Updating the links between nodes
        }
        temp = (data *)malloc(sizeof(data));                         // Dynamically allocating memory for a new node
        strcpy(temp ->fullName, dataNode ->fullName);                // Copying the values of the deleting node
        temp ->mtpData = dataNode ->mtpData;                         // to the new node
        free(dataNode);                                              // permanently deleting the node

        // Checking whether the head node is empty
        if (stdHead == NULL){
            temp ->next = NULL;                                      // Updating the links between nodes
            stdHead = temp;                                          // Updating the head node
            linkNode = temp;                                         // Initializing another node to use when connecting two sorted nodes
        } else {
            temp ->next = NULL;                                      // Updating the links between nodes
            linkNode ->next = temp;
            linkNode = temp;                                         // Updating the link node prior to connect the sorted nodes
        }
        ++ iter;                                                     // Updating the counter variable
    }
}

// Function to convert the time(string array) into minutes
long long timeConverter(char timeArr[]){ /*******************************************************************************************************/
    // Declaring the variables
    char hours[10], minutes[20];
    long long time = 0;
    // Getting the hours related data from the string and converting it to minutes
    char *pToken = strtok(timeArr, ":");
    strcpy(hours, pToken);
    time += atoll(hours)*60;
    // Getting the minutes related data from the string
    pToken = strtok(NULL, ":");
    strcpy(minutes, pToken);
    time += atoll(minutes);

    return time;
}

// Function to add data to the structure and check whether are there any missing entries in any row of a given file
// This function can also be used to check whether the given file can be opened or not
int addData(char fileName[],char c){ /***********************************************************************************************************/

    data *current, *temp, *prevNode, *arrNxtNode;                          // Pointer variables of structure type to add data to the structure
    char dataLine[80], name[40], participantsNo[20], duration[20];         // string arrays to store the data temporary
    long long time;
    int column = 0, isDuplicate, isMissing = 0,charVal=0;

    // Declaring variables
    FILE *filePointer;
    filePointer = fopen(fileName, "r");                                    // Opening the file for reading

    if (filePointer == NULL) return -1;                                    // Function will exit if the file cannot be open

    while (fgets(dataLine,80,filePointer)) {                               // Looping through the lines in a file
        ++headDetect;                                                            // to identify the head node and this will be useful to store data
        column = 1;                                                        // to separate the data in a row
        isDuplicate = 0;                                                   // Initializing the variable to zero to catch repeated entries
        // Splitting the data
        char* value = strtok(dataLine, ",");

        while (value != NULL && column <4) {

            if (column == 1) {                                             // If the condition is true
                strcpy(name,value);                                        // Coping the data to the name string

            } else if (column == 2 && c == 'p'){                           // If these conditions are true
                strcpy(participantsNo,value);                              // Coping the data to the participants number

            } else if (column == 3 && c == 't'){                           // If these conditions are true
                strcpy(duration,value);                                    // Coping the data to the time duration
            }

            value = strtok(NULL, ",");                                     // Splitting the data
            column++;                                                      // Incrementing the variable to figure out the three column's values
        }

        if (value == NULL && column < 4){                                  // Checking for  missing entries among any row of a given file
            isMissing = 1;
            break;
        }

        if (isMissing == 0)
        {
            // Calculating the integer value of the 1st character of the given host name
            if (( 'A' <= name[0]) &&  ( name[0] <= 'Z')){
                charVal = name[0] - 'A';
            } else if (( 'a' <= name[0]) &&  ( name[0] <= 'z')){
                charVal = name[0] - 'a';
            // If the character is not alphabet character
            }else {
                charVal = 26;
            }

            // Identifying the head node of the linked list data structure
            if (headDetect == 1){
                headCharValue = charVal;
            }
            // Going through the nodes to check whether the host name is already stored in the structure(according to alphabetic order)
            current = nodes[charVal];

            while (current != NULL){
                if (strcmp(current -> fullName, name)==0){                  // If the host name is already stored in the structure
                    isDuplicate = 1;                                        // to notify a repeated entries
                    // Appending the corresponding values
                    // Adding the values to the total
                    if (c == 'm') {
                        current -> mtpData++;
                        ++totalData;

                    } else if (c == 'p') {
                        current -> mtpData += atoll(participantsNo);
                        totalData += atoll(participantsNo);

                    } else if (c == 't') {
                        time = timeConverter(duration);
                        current -> mtpData += time;
                        totalData += time;
                    }
                }
                prevNode = current;                                         // Updating the previous node to current node
                current = current ->next;                                   // Jumping to the adjacent node
            }

            // If host name was not there in the structure
            // Then it will a generate a new node and store that data
            if (isDuplicate == 0){
                ++ totalEntries;
                // Dynamically allocating memory for the node
                temp = (data*)malloc(sizeof(data));
                strcpy(temp -> fullName, name);                             // Storing the host name
                // According to the given option it will store the data
                // Adding the values to the total
                if (c == 'm') {
                    temp -> mtpData = 1;
                    ++totalData;

                } else if (c == 'p') {
                    temp -> mtpData = atoll(participantsNo);
                    totalData += temp -> mtpData;

                } else if (c == 't') {
                    temp -> mtpData = timeConverter(duration);
                    totalData += temp -> mtpData;
                }

                // Adding the new data to the tail of the structure

                // when adding a non head node to the main linked list
                if (headDetect != 1){
                    arrNxtNode ->arrNxt = temp;                             // Updating the nodes
                    temp ->arrNxt = NULL;
                    arrNxtNode = temp;                                      // Updating the connecting node of the main linked list
                }

                //  When the head node of a given letter linked list is empty
                if (nodes[charVal] == NULL){
                    // when adding the head node to the linked list
                    if (headDetect == 1){
                        temp -> next = NULL;                                // Updating fields
                        temp ->arrNxt = NULL;
                        nodes[charVal] = temp;                              // Updating the head node of the alphabetical ordered linked list
                        arrNxtNode = temp;                                  // Connecting node to connect the nodes to the main linked list

                    } else {
                        temp -> next = NULL;                                // Updating the fields
                        nodes[charVal] = temp;                              // Updating the head node of the alphabetical ordered linked list
                    }

                //  When adding a non head node to the linked lists
                } else if (nodes[charVal] != NULL){
                    temp -> next = NULL;                                    // Updating the nodes
                    prevNode -> next = temp;                                // Updating the previous node to connect the new node
                }
            }
        }
    }

    fclose(filePointer);                                                    // Closing the file
    return isMissing;
}

// Function to check whether the given file is in the".csv" format
int csvChecker(char fileName[]){ /***************************************************************************************************************/
    // Declaring variables
    int len=0;

    while(fileName[len] != '\0') ++len;                                   // Calculating the length of the string

    int i,done=0;
    for(i=0;i<len-3;++i){
        // Checking for the conditions
        if (fileName[i]=='.' && fileName[i+1]=='c' && fileName[i+2]=='s' && fileName[i+3]=='v'){
            done = 1;
            break;
        }
    }
    return done;
}

// Function to check any punctuations present in the rows input
int rowsInputChecker(char str[]){ /**************************************************************************************************************/
    // Declaring variables
    int i=0,done = 1;

    for (i=0;str[i]!='\0';++i){
        // Using "isdigit" function to check whether the character is a number or not
        if(isdigit(str[i]) == 0){
            done = 0;
            break;
        }
    }
    return done;
}

/********************************************************** MAIN FUNCTION ***********************************************************************/
int main(int argc, char ** argv){

    // Declaring the variables
    files *currentFile = fileHeader, *temp;
    long long rows = 10, filesCount =0;
    int checkIn,isExit = 0, mtpCount = 0, isScaled = 0, isRandom = 0, is_lRandom = 0, filesOK = -1, dataOK = -1, missingEntry, rowsOK ;
    char mtpValue = 'm';

    /******************************* Variable Explanation **********************************

    checkIn           =               counter variable to go through the indexes of argv
    rowsOK            =               to notify whether the given row number has any punctuation marks
    isExit            =               to notify whether the program has to exit or not
    mtpCount          =               number of time that the three options are present
    isScaled          =               to notify whether the program should scaled the output or not
    isRandom          =               to notify whether the "-Random" scenario is present or not
    is_lRandom        =               to notify whether the "-l random" scenario is present or not
    filesOK           =               to notify whether the given files can be open and they all are in the .csv format
    dataOK            =               to notify whether the largest stored data is equal to zero
    missingEntry      =               to notify whether there any missing entries in a row of a given file
    rows              =               to store the value of number of rows to print in the bar chart
    mtpValue          =               to store the data option to plot
    filesCount        =               to calculate the number of file names user has entered

    */

    // Loop to iterate through the arguments
    for(checkIn=1;checkIn<argc;++checkIn){

        // Checking for "-l"
        if (argv[checkIn][0] == '-' && argv[checkIn][1] == 'l' && argv[checkIn][2] == '\0'){

            // Special case if the argv array ends with "-l"
            if (checkIn == argc-1){
                isExit = 1;
                is_lRandom = 1;
                printf("Not enough options for [-l]\n");
                printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
                break;

            } else {
                rows = atoll(argv[checkIn+1]);                          // Calculating the number of rows to plot
            }

            // Checking whether the given rows number has any punctuation marks
            rowsOK = rowsInputChecker(argv[checkIn+1]);

            // printing the corresponding error message for any negative number
             if (rows < 0){
                isExit = 1;
                is_lRandom = 1;
                printf("Invalid option(negative) for [-l]\n");
                printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
                break;

            // printing the error message for string inputs and punctuation occurrences
            } else if ((rows == 0 && argv[checkIn+1][0] != '0') || (rowsOK == 0)){
                isExit = 1;
                is_lRandom = 1;
                printf("Invalid options for [-l]\n");
                printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
                break;

            // Special case happens when user inputs zero as the number of rows to plot
            } else if (rows == 0 && argv[checkIn+1][0] == '0'){
                isExit = 1;
                is_lRandom = 1;
                break;
            }

            ++checkIn;                                           // Increment the counter by one to avoid checking the number of rows argument

        // Checking for "-m" , "-t" or "-p"
        } else if ((argv[checkIn][0] == '-') && (argv[checkIn][1] == 'm' || argv[checkIn][1] == 't' || argv[checkIn][1] == 'p') && (argv[checkIn][2] == '\0')){
            if ((mtpCount == 0) || (mtpValue != argv[checkIn][1])){
                mtpValue = argv[checkIn][1];
                ++ mtpCount;
            }
            // If there are different options entered more than once then the program should print an error message and exit
            if (mtpCount>1) isExit = 1;

        // Checking for "--scaled"
        } else if (argv[checkIn][0] == '-' && argv[checkIn][1] == '-' && argv[checkIn][2] == 's' && argv[checkIn][3] == 'c' && argv[checkIn][4] == 'a' && argv[checkIn][5] == 'l' && argv[checkIn][6] == 'e' && argv[checkIn][7] == 'd' && argv[checkIn][8] == '\0'){
            isScaled = 1;

        // Checking for "-" and "-Random"
        } else if ((argv[checkIn][0] == '-') && (argv[checkIn][1] == '\0' || argv[checkIn][1] != '\0')){
            isExit = 1;
            isRandom = 1;
            printf("Invalid option [%s]\n",argv[checkIn]);
            printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
            break;

        // Calculating the number of file names user has entered and adding them to the tail of the data structure
        } else {
            ++filesCount;
            // Allocating memory dynamically to store the file name in a separate node
            temp = (files *)malloc(sizeof(files));
            strcpy(temp ->fileName, argv[checkIn]);                     // Copying the file name to the structure node

            // Adding the data node to the tail of the structure
            if (fileHeader == NULL){
                temp -> next = NULL;
                fileHeader = temp;

            } else {
                currentFile = fileHeader;
                while (currentFile -> next != NULL){
                    currentFile = currentFile -> next;
                }
                currentFile -> next = temp;
            }
        }
    }

    // Printing the error message if different options have entered more than once
    if (isExit == 1 && isRandom == 0 && is_lRandom == 0) {
        printf("Cannot plot multiple parameters in same graph.\n");
        printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
    }

    // If all the above errors did not occur but if there are no files were given then it will print this error message
    if (isExit == 0 && filesCount == 0){
        printf("No input files were given\n");
        printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
    }

    if (isExit == 0 && filesCount > 0)
    {
        filesOK = 1;

        // Iterating through the file names structure to call the filenames user has input
        currentFile = fileHeader;

        while (currentFile != NULL){

            // Calling the function to check whether the user has input .csv format files
            if (csvChecker(currentFile ->fileName) == 0){
                filesOK = 0;
                printf("Only .csv files should be given as inputs.\n");
                break;
            }
            // Adding the data in the file to the data structure
            missingEntry = addData(currentFile ->fileName,mtpValue);

            // If those given files are cannot be opened
            if (missingEntry == -1){
                filesOK = 0;
                printf("Cannot open one or more given files\n");
                break;
            }

            // If there any missing entry in a given file
            if (missingEntry == 1) {
                filesOK = 0;
                printf("File/s contain wrong entries.\n");
                break;
            }
            currentFile = currentFile ->next;                        // updating the current node to it's next node
        }
    }

    // If given files are in the proper manner
    if (filesOK == 1)
    {
        sort(rows);                                                    // Calling the function to sort the data

        dataOK = 1;

        // Checking whether the largest data of a given type is equal to zero
        if (stdHead ->mtpData == 0){
            dataOK = 0;
            printf("No data to process\n");
        }

        if (dataOK == 1) plotData(rows, isScaled);                 // Calling the function to plot the data
    }
    free(fileHeader);                                              // Freeing the memory which was  allocated
    free(nodes[headCharValue]);                                   // for the two data structures
    free(stdHead);
    return 0;                                                      // End of the program
}
/************************************************************ THE END ***************************************************************************/
