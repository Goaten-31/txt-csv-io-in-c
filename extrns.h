#ifndef NEW_EXTRNS_H
#define NEW_EXTRNS_H

struct Contacts {
    char Name[64];
    int Age;
    char Email[64];
};

void fprintf_safe(FILE *fp, const char *str, int last) {
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

    // Setting up file path
    char path[256];
    char *user = getenv("USERPROFILE");
    if (user == NULL) return;
    snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);

    FILE *fp = fopen(path, "a+");
    if (fp == NULL) {
        perror("Save Error");
    }

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "Name,Age,Email\n");
    }

    fprintf(fp, "\"");
    fprintf_safe(fp, c->Name, 0);

    fprintf(fp,"%d", c->Age);

    fprintf(fp, "\"");
    fprintf_safe(fp, c->Email, 1);

    fclose(fp);
    printf("Contact saved locally.\n");
}

void search(const char *targetName) {
    // Generating file path
    char path[256];
    char *user = getenv("USERPROFILE");
    if (user != NULL) {
        snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);
    }

    // Opening the file in "read" mode
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

void filter(const int *filterAge) {
    if (filterAge == NULL) return;

    char path[256];
    char *user = getenv("USERPROFILE");
    if (user != NULL) {
        snprintf(path, sizeof(path), "%s\\Desktop\\contacts.csv", user);
    }

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open file in read mode.");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp);

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
    if (content == NULL) return;

    char path[256];
    char *user = getenv("USERPROFILE");
    if (user == NULL) {
        user = getenv("HOME");
    }

    if (user == NULL) {
        printf("Error: Could not find user directory.\n");
        return;
    }

    snprintf(path, sizeof(path), "%s\\Desktop\\testingClion.txt", user);

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
#endif //NEW_EXTRNS_H