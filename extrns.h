#ifndef NEW_EXTRNS_H
#define NEW_EXTRNS_H

struct Contacts {
    char Name[64];
    int Age;
    char Email[64];
};

/*
 * fprintfsafe was written to avoid any command injections, it's an "implicit" function
 * in the sense that it is only used within the header file, specifically for "saveCSV"
 */

void fprintfsafe(FILE *fp, const char *str, int last) {

    if (str == NULL) {
        fprintf(fp, ",");
        return;
    }

    const char *triggers = "=+-@";

    if (strchr(triggers, str[0])) {
        fprintf(fp, "'%s", str);
    } else {
        fprintf(fp, "%s", str);
    }

    fprintf(fp, last ? "\n" : ",");
}

void saveCSV(struct Contacts *c) {
    if (c == NULL) return;

    // generating the file path
    char path[256];
    char *user = getenv("USERPROFILE");
    if (user == NULL) return;
    snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);

    // opening file in append+ mode
    FILE *fp = fopen(path, "a+");
    if (fp == NULL) {
        perror("Save Error");
    }

    // checking if the file is empty, if so print the header
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "Name,Age,Email\n");
    }

    // printing contents into the file

    fprintf(fp, "\"");
    fprintfsafe(fp, c->Name, 0);

    // fprintf used since numbers are generally safe
    fprintf(fp,"%d", c->Age);

    fprintf(fp, "\"");
    fprintfsafe(fp, c->Email, 1);

    fclose(fp);
    printf("Contact saved successfully.\n");
}

void searchCSV(const char *targetName) {

    // generating file path
    char path[256];
    char *user = getenv("USERPROFILE");
    if (user != NULL) {
        snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);
    }

    // opening the file in "read" mode
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open file in read mode.");
        return;
    }

    // skipping the first line of the CSV file in the search
    char line[256];
    fgets(line, sizeof(line), fp);

    // search loop
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *nameInFile = strtok(line, ",");
        if (nameInFile != NULL && strcmp(nameInFile, targetName) == 0) {
            found = 1;
            char *age = strtok(nullptr, ",");
            char *email = strtok(nullptr, ",");

            if (email) email[strcspn(email, "\n")] = '\0';
            printf("Found Contact:\n Name:%s\n Age:%s\n Email:%s", nameInFile, age, email);
        }
    }
    if (!found) printf("Contact not found.\n");
    fclose(fp);
}

void filterCSV(const int *filterAge) {

    // generating the file path

    if (filterAge == NULL) return;

    char path[256];
    char *user = getenv("USERPROFILE");
    if (user != NULL) {
        snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);
    }

    // opening the file in read mode

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open file in read mode.");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp);

    // loop that does the actual filtering

    while (fgets(line, sizeof(line), fp)) {
        char *nametoken = strtok(line, ",");
        char *ageToken = strtok(nullptr, ",");
        char *emailToken = strtok(nullptr, ",");

        int ageInFile = atoi(ageToken);

        if (ageToken != NULL) {
            if (ageInFile > *filterAge) {
                if (emailToken) emailToken[strcspn(emailToken, "\n")] = '\0';
                printf("Found Contact:\n Name:%s\n Age:%s\n Email:%s", nametoken, ageToken, emailToken);
            }
        }
    }

}

void makeTxt(const char *content) {

    // generating file path
    if (content == NULL) return;

    char path[256];
    char *user = getenv("USERPROFILE");
    if (user == NULL) {
        user = getenv("HOME");
    }

    // handling the case for when the desired file isn't found

    if (user == NULL) {
        printf("Error: Could not find user directory.\n");
        return;
    }

    snprintf(path, sizeof(path), "%s\\Desktop\\testingClion.txt", user);

    // opening the file in write mode
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    fputs(content, fp);
    fputs("\n", fp);

    fclose(fp);

    printf("File saved successfully to: %s\n", path);
}

int getuserchoice(char *buf) {
    fgets(buf, sizeof(buf), stdin);
    return atoi(buf);
}

#endif //NEW_EXTRNS_H