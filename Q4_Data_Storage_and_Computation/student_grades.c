#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

// Structure to represent a student
typedef struct {
    char name[MAX_NAME_LENGTH];
    int programming_grade;
    int mobile_app_grade;
    int communications_grade;
} Student;

// Function to display all student data
void displayStudentData(Student students[], int n) {
    // printf("\n***************************************************\n");
    printf("                  Student Data\n");
    printf("***************************************************\n");

    for (int i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Programming in C Grade: %d\n", students[i].programming_grade);
        printf("Mobile Application Development Grade: %d\n", students[i].mobile_app_grade);
        printf("Communications Grade: %d\n", students[i].communications_grade);
        printf("----------------------------------------\n");
    }
}

int main() {
    int n;
    printf("\n****************************************\n");
    printf("**     Student Grade Entry System     **\n");
    printf("****************************************\n");
    printf("\nEnter the number of students (2 < n < 100): ");
    scanf("%d", &n);

    if (n < 2 || n >= 100) {
        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("XXXXX     Error: Invalid number of students.     XXXXX\n");
        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        return 1;
    }

    // Creating an array of Student structures
    Student students[MAX_STUDENTS];

    // Get student details from the user
    for (int i = 0; i < n; i++) {
        printf("\n***************************************************\n");
        printf("Student %d:\n", i + 1);
        printf("Enter full name: ");
        scanf(" %[^\n]", students[i].name); // Read full name with spaces

        printf("Enter Programming in C grade: ");
        scanf("%d", &students[i].programming_grade);

        printf("Enter Mobile Application Development grade: ");
        scanf("%d", &students[i].mobile_app_grade);

        printf("Enter Communications grade: ");
        scanf("%d", &students[i].communications_grade);
    }

    // Open the file for writing
    FILE *file = fopen("student_data.txt", "w"); // "w" for writing
    if (file == NULL) {
        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("XXXXX     Error: Unable to Open File for Writing     XXXXX\n");
        printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        return 1;
    }

    // Write student data to the file
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%d,%d,%d\n", students[i].name, 
                                        students[i].programming_grade,
                                        students[i].mobile_app_grade,
                                        students[i].communications_grade);
    }

    // Close the file
    fclose(file);

    printf("\n***************************************************\n");
    printf("Student data saved to student_data.txt\n");
    printf("\n***************************************************\n");

    // Prompt to display student data
    char choice;
    printf("Do you want to display all student data? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        displayStudentData(students, n);
    }

    return 0;
}