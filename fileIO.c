#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extrns.h"

// struct contained within the header file "extrns.h" line : 4
struct Contacts;

int main() {
    printf("1. Write\n");
    printf("2. Search\n");
    printf("3. Filter\n");
    printf("4. Exit\n");
    printf("Enter choice: ");

    int stchoice = 0;
    char schoice = 0;

    int filterage = 0;

    char buf[8];
    char buf2[8];

    char searchName[64];

    fgets(buf, sizeof(buf), stdin);
    stchoice = atoi(buf);

    do {
        if (stchoice == 1) {
            printf("1.CSV 2.txt ");

            fgets(buf2, sizeof(buf2), stdin);
            schoice = atoi(buf2);

            switch (schoice) {
                case 1:

                    struct Contacts *ptr = malloc(sizeof(struct Contacts));
                    if (ptr == NULL) return 1;
                    memset(ptr, 0, sizeof(*ptr));

                    printf("Enter name: ");
                    fgets(ptr -> Name, sizeof(ptr -> Name), stdin);
                    ptr->Name[strcspn(ptr -> Name, "\n")] = '\0';

                    printf("Enter age: ");
                    fgets(buf, sizeof(buf), stdin);
                    ptr -> Age = atoi(buf);

                    printf("Enter email: ");
                    fgets(ptr -> Email, sizeof(ptr -> Email), stdin);
                    ptr -> Email[strcspn(ptr -> Email, "\n")] = '\0';

                    saveCSV(ptr);
                    free(ptr);
                    break;

                case 2:

                    char *ptr1 = malloc(1024);
                    if (ptr1 == NULL) return 1;

                    printf("Enter .txt file content:\n");

                    if (fgets(ptr1, 1024, stdin)) {
                        ptr1[strcspn(ptr1, "\n")] = '\0';
                        makeTxt(ptr1);
                    }

                    free(ptr1);
                    break;

                default:
                    printf("Invalid Input\n");
            }
            break;
        } if (stchoice == 2) {

                printf("Enter name: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';
                search(searchName);
                break;
            } if (stchoice == 3) {
                memset(buf, 0, sizeof(buf));
                printf("Enter age: ");

                fgets(buf, sizeof(buf), stdin);
                filterage = atoi(buf);

                filter(&filterage);
            }

        if (stchoice == 4) {
            printf("Exiting...\n");
        }
    } while (stchoice != 4);

    return 0;
}