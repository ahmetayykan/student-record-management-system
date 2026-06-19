// Student Record Management System
// Include standard input/output library for printf, scanf, file operations
#include <stdio.h>
// Include string library for string operations like strcmp, strcpy
#include <string.h>
// Include standard library for exit, system functions
#include <stdlib.h>

// Define maximum number of students that can be stored
#define MAX_STUDENTS 100
// Define the filename where student data will be saved
#define FILENAME "students.txt"

// Define the Student structure to hold student information
struct Student {
    int id;                 // Unique student ID number
    char name[50];          // Student's full name (max 50 characters)
    char department[30];    // Department name or code (max 30 characters)
    float gpa;              // Grade Point Average (0.0 - 4.0)
};

// Function prototypes (declarations) - now with proper pointer parameters
void displayMenu();
void loadFromFile(struct Student *students, int *count, const char *filename);
void addStudent(struct Student *students, int *count);
void displayAllStudents(const struct Student *students, int count);
void searchStudentById(struct Student *students, int count);
void updateStudent(struct Student *students, int count);
void deleteStudent(struct Student *students, int *count);
void saveToFile(struct Student *students, int count, const char *filename);
int findStudentIndexById(struct Student *students, int count, int id);
void clearInputBuffer();

// Main function - entry point of the program
int main() {
    // Declare local array to store all student records (not global)
    struct Student students[MAX_STUDENTS];
    // Declare local counter to track the current number of students (not global)
    int studentCount = 0;
    // Variable to store user's menu choice
    int choice;

    // Display welcome message
    printf("\n========================================\n");
    printf("  Student Record Management System\n");
    printf("========================================\n");

    // Automatically load existing records from file at startup
    // Pass pointer to array and pointer to count
    loadFromFile(students, &studentCount, FILENAME);

    // Main program loop - continues until user chooses to exit
    do {
        // Display the menu options to the user
        displayMenu();
        // Prompt user for their choice
        printf("Enter your choice: ");

        // Read the user's choice with validation
        // Check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1) {
            // If scanf failed (user entered non-integer), display error
            printf("\nInvalid input! Please enter a number.\n");
            // Clear the input buffer to remove invalid input
            clearInputBuffer();
            // Set choice to invalid value to continue loop
            choice = -1;
            // Skip rest of loop iteration
            continue;
        }

        // Clear the input buffer to prevent issues with subsequent inputs
        clearInputBuffer();

        // Process user's choice using switch statement
        switch(choice) {
            case 1:
                // Load records from file - pass pointers
                loadFromFile(students, &studentCount, FILENAME);
                break;
            case 2:
                // Add a new student record - pass array pointer and count pointer
                addStudent(students, &studentCount);
                break;
            case 3:
                // Display all student records - pass array pointer and count value
                displayAllStudents(students, studentCount);
                break;
            case 4:
                // Search for a student by ID - pass array pointer and count
                searchStudentById(students, studentCount);
                break;
            case 5:
                // Update existing student information - pass array pointer and count
                updateStudent(students, studentCount);
                break;
            case 6:
                // Delete a student record - pass array pointer and count pointer
                deleteStudent(students, &studentCount);
                break;
            case 7:
                // Save all records to file - pass array pointer, count, and filename
                saveToFile(students, studentCount, FILENAME);
                break;
            case 0:
                // Save before exiting and display goodbye message
                saveToFile(students, studentCount, FILENAME);
                printf("\nThank you for using the system. Goodbye!\n");
                break;
            default:
                // Handle invalid menu choices
                printf("\nInvalid choice! Please try again.\n");
        }
    } while(choice != 0); // Continue loop until user selects exit option

    // Return 0 to indicate successful program execution
    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\n*****************************\n");
    printf("Student Record Management\n");
    printf("******************************\n");
    printf("1. Load records from file\n");
    printf("2. Add new student\n");
    printf("3. Display all students\n");
    printf("4. Search student by ID\n");
    printf("5. Update student information\n");
    printf("6. Delete student\n");
    printf("7. Save records to file\n");
    printf("0. Exit\n");
    printf("******************************\n");
}

// Function to load student records from file
// Parameters: pointer to students array, pointer to count, filename
void loadFromFile(struct Student *students, int *count, const char *filename) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    // Check if file exists and was opened successfully
    if (file == NULL) {
        // File doesn't exist (first run) - display informational message
        printf("\nNo existing data file found. Starting with empty records.\n");
        // Return to caller since there's nothing to load
        return;
    }

    // Reset student count to zero before loading (dereference pointer)
    *count = 0;

    // Read records from file until end of file or array is full
    // Access array elements using pointer arithmetic
    while (*count < MAX_STUDENTS &&
           fscanf(file, "%d %s %s %f",
                  &students[*count].id,
                  students[*count].name,
                  students[*count].department,
                  &students[*count].gpa) == 4) {
        // Increment counter for each successfully read record (dereference pointer)
        (*count)++;
    }

    // Close the file to free resources
    fclose(file);

    // Display success message with number of records loaded
    printf("\n%d record(s) loaded successfully from %s\n", *count, filename);
}

// Function to add a new student record
// Parameters: pointer to students array, pointer to count
void addStudent(struct Student *students, int *count) {
    // Check if the array is full (dereference count pointer)
    if (*count >= MAX_STUDENTS) {
        // Display error message if maximum capacity reached
        printf("\nError: Student database is full! Cannot add more students.\n");
        // Return to caller without adding
        return;
    }

    // Declare a temporary student structure to hold new data
    struct Student newStudent;

    printf("\n--- Add New Student ---\n");

    // Prompt for and read student ID with validation
    printf("Enter Student ID: ");
    // Check if scanf successfully read an integer
    if (scanf("%d", &newStudent.id) != 1) {
        // Display error message if input is not a valid integer
        printf("\nError: Invalid input for ID!\n");
        // Clear input buffer
        clearInputBuffer();
        // Return without adding
        return;
    }
    clearInputBuffer();

    // Check if ID already exists using helper function
    // Pass pointer to array and current count value
    if (findStudentIndexById(students, *count, newStudent.id) != -1) {
        // Display error if duplicate ID found
        printf("\nError: A student with ID %d already exists!\n", newStudent.id);
        // Return without adding the duplicate
        return;
    }

    // Prompt for and read student name with validation
    printf("Enter Name (use underscore for spaces, e.g., Ahmet_Aykan_Cakmak): ");
    // Check if scanf successfully read a string
    if (scanf("%49s", newStudent.name) != 1) {
        // Display error if input failed
        printf("\nError: Invalid input for name!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Prompt for and read department with validation
    printf("Enter Department: ");
    // Check if scanf successfully read a string
    if (scanf("%29s", newStudent.department) != 1) {
        // Display error if input failed
        printf("\nError: Invalid input for department!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Prompt for and read GPA with validation
    printf("Enter GPA (0.0 - 4.0): ");
    // Check if scanf successfully read a float
    if (scanf("%f", &newStudent.gpa) != 1) {
        // Display error if input is not a valid number
        printf("\nError: Invalid input for GPA!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Validate GPA is within acceptable range
    if (newStudent.gpa < 0.0 || newStudent.gpa > 4.0) {
        // Display error for invalid GPA
        printf("\nError: Invalid GPA! Must be between 0.0 and 4.0.\n");
        // Return without adding invalid record
        return;
    }

    // Copy the new student data into the array at the current count position
    // Use pointer to access array element
    students[*count] = newStudent;
    // Increment the student count (dereference pointer to modify value)
    (*count)++;

    // Display success message
    printf("\nStudent added successfully!\n");
}

// Function to display all student records in a formatted table
// Parameters: const pointer to students array (read-only), count value
void displayAllStudents(const struct Student *students, int count) {
    // Check if there are any students to display
    if (count == 0) {
        // Display message if no records exist
        printf("\nNo records available.\n");
        // Return to caller
        return;
    }

    printf("\n--- All Student Records ---\n");
    // Print table header
    printf("%-10s %-20s %-15s %-6s\n", "ID", "Name", "Department", "GPA");
    // Print separator line
    printf("-----------------------------------------------------------\n");

    // Loop through all students in the array using pointer
    for (int i = 0; i < count; i++) {
        // Print each student's information in formatted columns
        // Access array elements through pointer
        printf("%-10d %-20s %-15s %-6.2f\n",
               students[i].id,
               students[i].name,
               students[i].department,
               students[i].gpa);
    }
    // Print bottom separator
    printf("-----------------------------------------------------------\n");
    // Display total count
    printf("Total Students: %d\n", count);
}

// Function to search for a student by their ID
// Parameters: pointer to students array, count value
void searchStudentById(struct Student *students, int count) {
    int searchId; // Variable to store the ID to search for

    // Prompt user for the ID to search with validation
    printf("\nEnter Student ID to search: ");
    // Check if scanf successfully read an integer
    if (scanf("%d", &searchId) != 1) {
        // Display error if input is invalid
        printf("\nError: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Find the index of the student with given ID
    // Pass pointer to array and count
    int index = findStudentIndexById(students, count, searchId);

    // Check if student was found
    if (index == -1) {
        // Display not found message
        printf("\nStudent not found.\n");
        // Return to caller
        return;
    }

    // Display the found student's information using pointer
    printf("\n--- Student Found ---\n");
    printf("ID:         %d\n", students[index].id);
    printf("Name:       %s\n", students[index].name);
    printf("Department: %s\n", students[index].department);
    printf("GPA:        %.2f\n", students[index].gpa);
}

// Function to update an existing student's information
// Parameters: pointer to students array, count value
void updateStudent(struct Student *students, int count) {
    int updateId; // Variable to store ID of student to update

    // Prompt user for the ID to update with validation
    printf("\nEnter Student ID to update: ");
    // Check if scanf successfully read an integer
    if (scanf("%d", &updateId) != 1) {
        // Display error if input is invalid
        printf("\nError: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Find the student's index using pointer to array
    int index = findStudentIndexById(students, count, updateId);

    // Check if student exists
    if (index == -1) {
        // Display error if not found
        printf("\nStudent not found.\n");
        // Return to caller
        return;
    }

    // Display current information using pointer to struct
    printf("\n--- Current Information ---\n");
    printf("ID:         %d\n", students[index].id);
    printf("Name:       %s\n", students[index].name);
    printf("Department: %s\n", students[index].department);
    printf("GPA:        %.2f\n", students[index].gpa);

    int choice; // Variable to store which field to update

    // Display update options menu
    printf("\nWhat would you like to update?\n");
    printf("1. Name\n");
    printf("2. Department\n");
    printf("3. GPA\n");
    printf("4. All information\n");
    printf("0. Cancel\n");
    printf("Enter choice: ");

    // Read choice with validation
    if (scanf("%d", &choice) != 1) {
        printf("\nError: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Declare temporary variable for GPA validation
    float tempGPA;

    // Process update choice
    switch(choice) {
        case 1:
            // Update name only with validation
            printf("Enter new Name: ");
            if (scanf("%49s", students[index].name) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();
            printf("\nName updated successfully.\n");
            break;
        case 2:
            // Update department only with validation
            printf("Enter new Department: ");
            if (scanf("%29s", students[index].department) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();
            printf("\nDepartment updated successfully.\n");
            break;
        case 3:
            // Update GPA only with proper validation
            printf("Enter new GPA: ");
            // Read into temporary variable first
            if (scanf("%f", &tempGPA) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();
            // Validate GPA range before updating struct
            if (tempGPA < 0.0 || tempGPA > 4.0) {
                // Display error and do NOT update the struct
                printf("\nError: Invalid GPA! Must be between 0.0 and 4.0. Update cancelled.\n");
            } else {
                // Only update if valid
                students[index].gpa = tempGPA;
                printf("\nGPA updated successfully.\n");
            }
            break;
        case 4:
            // Update all fields with full validation
            printf("Enter new Name: ");
            if (scanf("%49s", students[index].name) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            printf("Enter new Department: ");
            if (scanf("%29s", students[index].department) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            printf("Enter new GPA: ");
            // Read into temporary variable first
            if (scanf("%f", &tempGPA) != 1) {
                printf("\nError: Invalid input!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            // Validate GPA before updating
            if (tempGPA < 0.0 || tempGPA > 4.0) {
                // If GPA invalid, cancel entire update
                printf("\nError: Invalid GPA! Update cancelled.\n");
                return;
            }

            // Only update GPA if valid
            students[index].gpa = tempGPA;
            printf("\nAll information updated successfully.\n");
            break;
        case 0:
            // Cancel update operation
            printf("\nUpdate cancelled.\n");
            break;
        default:
            // Handle invalid choice
            printf("\nInvalid choice!\n");
    }
}

// Function to delete a student record
// Parameters: pointer to students array, pointer to count
void deleteStudent(struct Student *students, int *count) {
    int deleteId; // Variable to store ID of student to delete

    // Prompt for ID to delete with validation
    printf("\nEnter Student ID to delete: ");
    // Check if scanf successfully read an integer
    if (scanf("%d", &deleteId) != 1) {
        // Display error if input is invalid
        printf("\nError: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Find the student's index using pointer to array
    int index = findStudentIndexById(students, *count, deleteId);

    // Check if student exists
    if (index == -1) {
        // Display error if not found
        printf("\nStudent not found.\n");
        // Return to caller
        return;
    }

    // Display information of student to be deleted
    printf("\nDeleting student: %s (ID: %d)\n", students[index].name, students[index].id);

    // Use PDF's recommended simple method:
    // Move the LAST student to the deleted position
    // This is more efficient than shifting all elements
    students[index] = students[*count - 1];

    // Decrease the student count (dereference pointer)
    (*count)--;

    // Display success message
    printf("Record deleted successfully.\n");
}

// Function to save all student records to file
// Parameters: pointer to students array, count value, filename
void saveToFile(struct Student *students, int count, const char *filename) {
    // Open file in write mode (overwrites existing content)
    FILE *file = fopen(filename, "w");

    // Check if file was opened successfully
    if (file == NULL) {
        // Display error message if file couldn't be opened
        printf("\nError: Could not open file for writing!\n");
        // Return to caller
        return;
    }

    // Loop through all students and write to file using pointer
    for (int i = 0; i < count; i++) {
        // Write student data in formatted text (space-separated)
        // Access array elements through pointer
        fprintf(file, "%d %s %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].department,
                students[i].gpa);
    }

    // Close the file to ensure data is written
    fclose(file);

    // Display success message with filename
    printf("\nRecords saved successfully to %s\n", filename);
}

// Helper function to find a student's index by their ID
// Parameters: pointer to students array, count value, id to search
// Returns the index if found, or -1 if not found
int findStudentIndexById(struct Student *students, int count, int id) {
    // Loop through all students using pointer to array
    for (int i = 0; i < count; i++) {
        // Check if current student's ID matches the search ID
        if (students[i].id == id) {
            // Return the index where student was found
            return i;
        }
    }
    // Return -1 to indicate student was not found
    return -1;
}

// Helper function to clear the input buffer
// This prevents issues with leftover characters in stdin
void clearInputBuffer() {
    int c; // Variable to temporarily store characters
    // Read and discard characters until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF);
}