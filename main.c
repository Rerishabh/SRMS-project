#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    char roll[30];
    char name[50];
    float marks;
};

char currentRole[20], currentUser[50];

/* --------------------------- LOGIN SYSTEM --------------------------- */
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[20];

    int attempts = 0;

    while (attempts < 3) {
        printf("========= LOGIN =========\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        FILE *fp = fopen(CREDENTIAL_FILE, "r");
        if (!fp) {
            printf("Error: credentials.txt not found!\n");
            return 0;
        }

        while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
            if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
                strcpy(currentRole, fileRole);
                strcpy(currentUser, fileUser);
                fclose(fp);
                return 1;
            }
        }

        fclose(fp);
        attempts++;
        printf("\nInvalid credentials! Attempts left: %d\n\n", 3 - attempts);
    }

    return 0;
}

/* ----------------------- FUNCTION DECLARATIONS ----------------------- */
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* ----------------------------- MAIN ---------------------------------- */
int main() {
    if (loginSystem()) {
        if (strcmp(currentRole, "ADMIN") == 0) adminMenu();
        else if (strcmp(currentRole, "USER") == 0) userMenu();
        else if (strcmp(currentRole, "STAFF") == 0) staffMenu();
        else guestMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}

/* ----------------------------- ADMIN MENU ---------------------------- */
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3. Search student\n");
        printf("4. Update (Rename/Marks) student\n");
        printf("5. Delete student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }

    } while (1);
}

/* ----------------------------- USER MENU ----------------------------- */
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: return;
            default: printf("Invalid choice!\n");
        }
    } while(1);
}

/* ----------------------------- STAFF MENU ---------------------------- */
void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display students\n");
        printf("2. Search student\n");
        printf("3. Update (Rename/Marks)\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    } while(1);
}

/* ----------------------------- GUEST MENU ---------------------------- */
void guestMenu() {
    int choice;
    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display students\n");
        printf("2. Search student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while(1);
}

/* ---------------------------- ADD STUDENT ---------------------------- */
void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter roll: ");
    scanf("%s", s.roll);
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%s %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student added!\n");
}

/* --------------------------- DISPLAY STUDENTS ------------------------ */
void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    printf("\nROLL\t\tNAME\t\tMARKS\n");

    while (fscanf(fp, "%s %s %f", s.roll, s.name, &s.marks) == 3) {
        printf("%s\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

/* --------------------------- SEARCH STUDENT -------------------------- */
void searchStudent() {
    struct Student s;
    char key[50];
    int found = 0, choice;

    printf("Search by:\n1. Roll\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    printf("Enter search value: ");
    scanf("%s", key);

    FILE *fp = fopen(STUDENT_FILE, "r");

    while (fscanf(fp, "%s %s %f", s.roll, s.name, &s.marks) == 3) {
        if ((choice == 1 && strcmp(key, s.roll) == 0) ||
            (choice == 2 && strcmp(key, s.name) == 0)) {
            printf("%s\t%s\t%.2f\n", s.roll, s.name, s.marks);
            found = 1;
        }
    }

    if (!found) printf("No matching record found!\n");
    fclose(fp);
}

/* --------------------------- UPDATE STUDENT -------------------------- */
void updateStudent() {
    struct Student s;
    char roll[30];
    int found = 0;

    printf("Enter roll to update: ");
    scanf("%s", roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%s %s %f", s.roll, s.name, &s.marks) == 3) {
        if (strcmp(roll, s.roll) == 0) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%s %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) printf("Record updated!\n");
    else printf("Record not found!\n");
}

/* --------------------------- DELETE STUDENT -------------------------- */
void deleteStudent() {
    struct Student s;
    char roll[30];
    int found = 0;

    printf("Enter roll to delete: ");
    scanf("%s", roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%s %s %f", s.roll, s.name, &s.marks) == 3) {
        if (strcmp(roll, s.roll) != 0) {
            fprintf(temp, "%s %s %.2f\n", s.roll, s.name, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) printf("Record deleted!\n");
    else printf("Record not found!\n");
}
