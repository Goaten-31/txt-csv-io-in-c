#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extrns.h"

/* struct contained within the header file "extrns.h" line : 4
   externs also contains the functions: saveCSV, searchCSV, filterCSV, makeTxt, and getuserchoice */
struct Contacts;

int main() {

    // prompting the user to choose their desired action

    printf("1. Write\n");
    printf("2. Search\n");
    printf("3. Filter\n");
    printf("4. Exit\n");
    printf("Enter choice: ");

    // setting variables:

    /*
    first, variables that will hold the numbers representing
    the choices of the user
    */

    int STchoice = 0;
    int SNchoice = 0;
    int filterage = 0;

    /*
    then buffers to hold the numeric values as chars that will then
    be turned into ints to be processed in a switch statement
    */

    char buf[8];
    char buf2[8];
    char agebuf[8];

    // meant to hold the name the user inputs when they chose "2. Search"

    char searchName[64];

    // getuserchoice found in "extrns.h" line : 159
    STchoice = getuserchoice(&buf[8]);

    while (STchoice != 4) {
        switch (STchoice) {
            case 1: {
                //prompt user to choose the type of file
                printf("1.CSV\n2.txt\n ");
                SNchoice = getuserchoice(&buf2[8]);

                switch (SNchoice) {
                    case 1:
                        /*
                            allocating memory for the struct
                            then asking the user for the info they want to enter
                            saveCSV is found in "extrns.h" line : 27
                        */

                        struct Contacts *ptrCSV = malloc(sizeof(struct Contacts));
                        if (ptrCSV == NULL) return 1;
                        memset(ptrCSV, 0, sizeof(*ptrCSV));

                        printf("Enter name: ");
                        fgets(ptrCSV -> Name, sizeof(ptrCSV -> Name), stdin);
                        ptrCSV->Name[strcspn(ptrCSV -> Name, "\n")] = '\0';

                        memset(agebuf, 0, sizeof(agebuf));
                        printf("Enter age: ");
                        fgets(agebuf, sizeof(agebuf), stdin);
                        ptrCSV -> Age = atoi(agebuf);

                        printf("Enter email: ");
                        fgets(ptrCSV -> Email, sizeof(ptrCSV -> Email), stdin);
                        ptrCSV -> Email[strcspn(ptrCSV -> Email, "\n")] = '\0';

                        saveCSV(ptrCSV);
                        free(ptrCSV);
                        break;

                    case 2:

                        /* allocating memory for and printing contents into the .txt file
                         * makeTxt found in "extrns.h" line : 129
                         */

                        char *ptrTxt = malloc(1024);
                        if (ptrTxt == NULL) return 1;

                        printf("Enter .txt file content: (max 1024 chars)\n");

                        if (fgets(ptrTxt, 1024, stdin)) {
                            ptrTxt[strcspn(ptrTxt, "\n")] = '\0';
                            makeTxt(ptrTxt);
                        }

                        free(ptrTxt);
                        break;

                    default:
                        printf("Invalid Input\n");
                        break;

                }
                STchoice = 4;

            } case 2: {

                /* prompting user to enter in the name they want to search for
                 * searchCSV is found in "extrns.h" line: 58
                 */

                printf("Enter name: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';
                searchCSV(searchName);
                STchoice = 4;

            } case 3: {
                // clearing buffer
                memset(agebuf, 0, sizeof(agebuf));

                /* prompting user to enter the age they want to filter by
                 * filterCSV found in "extrns.h" line : 94
                 */
                printf("Enter age: ");
                filterage = getuserchoice(&buf[8]);

                filterCSV(&filterage);
                STchoice = 4;
            }

            default:
                printf("Invalid Input\n");
                break;

        }

    }
    printf("Exiting Program.\n");

    return 0;
}