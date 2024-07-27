#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMES 100 // Defining a maximum number of names

// Function to count the number of names in an array
int countNames(char **names, int size) {
    return size;
}

// Function to sort names in ascending order
void sortAscending(char **names, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                char *temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }
        }
    }
}

// Function to sort names in descending order
void sortDescending(char **names, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(names[i], names[j]) < 0) {
                char *temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }
        }
    }
}

// Function to read names from a file
int readNamesFromFile(char **names, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Removing trailing newline
        names[i] = strdup(line); // Allocating memory and copying the name
        i++;
    }

    fclose(file);
    return i;
}

int main() {
    char *names[MAX_NAMES]; // Array to store names
    int size = 0;

    // Read names from a file
    size = readNamesFromFile(names, "names.txt");
    if (size == 0) {
        return 1; // Exit if file reading fails
    }

    // Array of function pointers
    void (*functions[2])(char **, int) = {sortAscending, sortDescending};

    char continueChoice;

    do {
        // Get user input for function choice
        int functionChoice;
        printf("\n***************************************************\n");
        printf("Which operation would you like to perform?\n");
        printf("Type '1' to sort names\n");
        printf("Type '2' to count the names\n\n");
        printf("Enter your choice: ");
        scanf("%d", &functionChoice);

        // Get user input for sorting order (if sorting is chosen)
        char order[5]; // Allocate space for "asc" or "desc"
        if (functionChoice == 1) {
            printf("\n***************************************************\n");
            printf("Type 'asc' to sort in ascending order or 'desc' for descending)\n\n");
            printf("Enter your choice: ");
            scanf("%4s", order); // Read up to 4 characters
        }

        // Call the selected function
        if (functionChoice == 1) {
            // Set the sorting function based on user input
            void (*sortFunction)(char **, int) = NULL;
            if (strcmp(order, "asc") == 0) {
                sortFunction = functions[0]; // Sort ascending
            } else if (strcmp(order, "desc") == 0) {
                sortFunction = functions[1]; // Sort descending
            } else {
                printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
                printf("XXXXX     Error: Invalid Sorting Order     XXXXX\n");
                printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
                continue; // Skip to the next iteration of the loop
            }

            // Call the sorting function
            sortFunction(names, size);

            // Print the sorted names
            
            printf("                  Sorted names\n");
            printf("---------------------------------------------------\n");
            for (int i = 0; i < size; i++) {
                printf("%s\n", names[i]);
            }
            printf("---------------------------------------------------\n");
        } else if (functionChoice == 2) {
            // Call the count names function
            int nameCount = countNames(names, size);
            printf("\n***************************************************\n");
            printf("\nNumber of names: %d\n", nameCount);
            printf("\n***************************************************\n");
        } else {
            printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
            printf("\nXXXXX     Error: Invalid Function Choice     XXXXX\n");
            printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
            continue; // Skip to the next iteration of the loop
        }

        // Ask the user to continue or end
        printf("Enter any digit to run another function or type 'end' to terminate: ");
        scanf(" %c", &continueChoice);

    } while (continueChoice != 'e' && continueChoice != 'E');

    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    printf("\nXXXXX     PROGRAM TERMINATED!!!     XXXXX\n");
    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(names[i]);
    }

    return 0;
}