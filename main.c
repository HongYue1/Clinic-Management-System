#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct Patient
{
    char name[50];
    int age;
    char gender;
    int id;
    struct Patient *next;
};

struct Slot
{
    char time[20];
    int isReserved;
    int patientId;
};

struct Slot slots[5] = {
    {"2pm to 2:30pm", 0, 0},
    {"2:30pm to 3pm", 0, 0},
    {"3pm to 3:30pm", 0, 0},
    {"4pm to 4:30pm", 0, 0},
    {"4:30pm to 5pm", 0, 0}};

struct Patient *head = NULL;
int length = 0;

void Welcome_Screen();
int login();
void Admin_Window();
void Add_Patient_Window();
void Add_Patient(char name[], int age, char gender, int id);
void Edit_Patient_Record();
void reserveSlot();
void Cancel_Reservations();
void Print_Reservations();
void Print_Patients();
void User_Window();
void View_Patient_Record();
void View_Todays_Reservations();
void clearInputBuffer();

int main()
{
    Welcome_Screen();
    Admin_Window();

    return 0;
}

void Welcome_Screen()
{
    system("cls"); // Clear the console screen, should be replaced with "clear" in case of linux

    // Print a header
    printf("\033[1;32m"); // Set color to green
    printf("**********************************\n");
    printf("* Welcome to the Clinic System! *\n");
    printf("**********************************\n");
    printf("\033[0m"); // Reset color

    // Print a menu
    printf("Please choose an option:\n");
    printf("1. Admin Mode\n");
    printf("2. User Mode\n");
    printf("3. Exit\n");

    while (1)
    {
        int choice = 0;

        // Get user input
        scanf("%d", &choice);
        clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // Admin Mode
            printf("Admin Mode selected\n");
            sleep(1);
            system("cls"); // Clear the console screen
            if (login())   // login
            {
                Admin_Window();
            }
            break;

        case 2:
            // User Mode
            printf("User Mode selected\n");
            sleep(1);
            User_Window();
            break;

        case 3:
            // Exit
            printf("Exiting the system...\n");
            exit(0); // Exit Success

        default:
            printf("\033[1;31m"); // Set color to red
            printf("Invalid choice! Please choose a valid option.\n");
            printf("\033[0m"); // Reset color
            break;
        }
    }
}

int login()
{
    int password_tries = 0;
    char password[5];

    while (password_tries < 3)
    {
        printf("Enter the password: ");
        scanf("%s", password);
        clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input

        if (strcmp(password, "1234") == 0)
        {
            return 1; // Password is correct
        }
        else
        {
            password_tries++;
            printf("\033[1;31m"); // Set color to red
            printf("Incorrect password! Please try again.\n");
            printf("\033[0m"); // Reset color
            sleep(1);          // Delay for 1 second
        }
    }

    // Too many incorrect password attempts
    printf("\033[1;31m"); // Set color to red
    printf("Too many incorrect password attempts. Exiting the system...\n");
    printf("\033[0m"); // Reset color
    sleep(1);          // Delay for 1 second
    exit(0);           // Exit
}

void Admin_Window()
{
    system("cls"); // Clear the console screen

    // print the menu
    printf("Please choose an option:\n");
    printf("1. Add a new patient record.\n");
    printf("2. Edit patient record.\n");
    printf("3. Reserve a slot with the doctor.\n");
    printf("4. Cancel reservation.\n");
    printf("5. Print all patients.\n");
    printf("6. Print all reservations.\n");
    printf("7. Back.\n");

    while (1) // Loop until the user chooses to go back
    {
        int choice = 0;

        // Get user input
        scanf("%d", &choice);
        clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // Add a new patient record
            printf("New patient record selected.\n");
            sleep(1); // Pause for 1 second
            Add_Patient_Window();
            break;

        case 2:
            // Edit a patient record
            printf("Edit patient record selected.\n");
            sleep(1);
            Edit_Patient_Record();
            break;

        case 3:
            // Reserve a slot
            printf("Reserve a slot with the doctor selected.\n");
            sleep(1);
            reserveSlot();
            break;

        case 4:
            // Cancel reservation
            printf("Cancel reservation selected.\n");
            sleep(1);
            Cancel_Reservations();
            break;

        case 5:
            // Print all patients
            printf("Print all patients selected.\n");
            sleep(1);
            Print_Patients();
            sleep(1);
            printf("\nType (e) to go back when you are ready: ");

            while (1) // Loop until the user types 'e'
            {
                char e;
                fflush(stdin); // Flush the input buffer

                scanf(" %c", &e);
                clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                if (e == 'e')
                {
                    system("cls");  // Clear the console screen
                    Admin_Window(); // Go back to the admin window
                    break;
                }
            }
            break;

        case 6:
            // Print all reservations
            printf("Print all reservations selected.\n");
            sleep(1);
            system("cls"); // Clear the console screen
            Print_Reservations();
            sleep(1);
            printf("\nType 'e' to go back when you are ready: ");

            while (1) // Loop until the user types 'e'
            {
                char e;
                fflush(stdin); // Flush the input buffer

                scanf(" %c", &e);
                clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                if (e == 'e')
                {
                    system("cls");  // Clear the console screen
                    Admin_Window(); // Go back to the admin window
                    break;
                }
            }
            break;

        case 7:
            // Back option
            Welcome_Screen();
            break;

        default:
            printf("\033[1;31m"); // Set color to red
            printf("Invalid choice! Please choose a valid option.\n");
            printf("\033[0m"); // Reset color
            break;
        }
    }
}

void Add_Patient_Window()
{
    system("cls"); // Clear the console screen

    char name[50];
    int age;
    char gender;
    int id;

    printf("Enter patient information:\n");
    printf("Name: ");
    fgets(name, sizeof(name), stdin); // to get the name with space included
    name[strcspn(name, "\n")] = 0;    // Remove the newline character from the name which fgets() adds to prevent problems later

    while (1)
    {
        printf("Age: ");
        if (scanf("%d", &age) != 1 || age == 0) // Check if the entered number is a non zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a valid age.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid age is entered
        }
    }

    while (1)
    {
        printf("Gender (M or F): ");
        if (scanf(" %c", &gender) != 1 || (gender != 'M' && gender != 'F')) // Check if the entered gender is a character, either 'M' or 'F'
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter either 'M' or 'F' for gender.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid gender is entered
        }
    }

    while (1)
    {
        printf("ID: ");
        if (scanf("%d", &id) != 1 || id == 0) // Check if the entered ID is a non-zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a non-zero ID.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid ID is entered
        }
    }

    // Call the Add_Patient function
    Add_Patient(name, age, gender, id);
}

void Add_Patient(char name[], int age, char gender, int id)
{
    // Check if the ID already exists
    struct Patient *current = head; // Pointer to traverse the linked list
    while (current != NULL)
    {
        if (current->id == id) // If the ID already exists
        {
            printf("\033[1;31m"); // Set color to red
            printf("ID already exists. Entry rejected.\n");
            printf("\033[0m"); // Reset color
            sleep(1);
            Add_Patient_Window(); // Call the function to add a new patient
        }
        current = current->next; // Move to the next node
    }

    // Create a new patient node
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    strcpy(newPatient->name, name); // Copy the name to the new patient node
    newPatient->age = age;          // Assign the age
    newPatient->gender = gender;    // Assign the gender
    newPatient->id = id;            // Assign the ID
    newPatient->next = NULL;        // Set the next pointer to NULL

    // If the linked list is empty, make the new patient the head
    if (head == NULL)
    {
        head = newPatient;
    }
    else
    {
        // Find the last node and add the new patient to the end
        struct Patient *last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = newPatient;
    }

    length++; // Increment the length of the linked list

    printf("Patient added Successfully!\n");
    sleep(1);
    Admin_Window(); // Call the function to go back to the admin window
}

void Edit_Patient_Record()
{
    system("cls"); // Clear the console screen

    int id;
    printf("Enter the Patient ID: ");

    while (1)
    {
        if (scanf("%d", &id) != 1 || id == 0) // Check if the entered ID is a non-zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a non-zero ID.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid ID is entered
        }
    }

    struct Patient *current = head; // Pointer to traverse the linked list
    while (current != NULL)
    {
        if (current->id == id) // If the patient with the given ID is found
        {
            // Edit the patient information
            printf("Enter new patient information:\n");
            printf("Name: ");
            fgets(current->name, sizeof(current->name), stdin);
            current->name[strcspn(current->name, "\n")] = 0; // Remove the newline character

            while (1)
            {
                printf("Age: ");
                if (scanf("%d", &(current->age)) != 1 || current->age == 0) // Check if the entered number is a non zero integer
                {
                    printf("\033[1;31m"); // Set color to red
                    printf("Invalid input. Please enter a valid age.\n");
                    printf("\033[0m"); // Reset color

                    clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                }
                else
                {
                    clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                    break;              // Exit the loop if a valid age is entered
                }
            }

            while (1)
            {
                printf("Gender (M or F): ");
                // Check if the entered gender is a character, either 'M' or 'F'
                if (scanf(" %c", &(current->gender)) != 1 || (current->gender != 'M' && current->gender != 'F'))
                {
                    printf("\033[1;31m"); // Set color to red
                    printf("Invalid input. Please enter either 'M' or 'F' for gender.\n");
                    printf("\033[0m");  // Reset color
                    clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                }
                else
                {
                    clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
                    break;              // Exit the loop if a valid gender is entered
                }
            }

            printf("Patient record updated successfully.\n");
            sleep(1);

            Admin_Window(); // Call the function to go back to the admin window
        }
        current = current->next; // Move to the next node
    }

    // If we reach here, it means the patient with the given ID was not found
    printf("\033[1;31m"); // Set color to red
    printf("Incorrect ID! No patient found with the given ID.\n");
    printf("\033[0m"); // Reset color
    sleep(2);

    Admin_Window(); // Call the function to go back to the admin window
}

void reserveSlot()
{
    system("cls"); // Clear the console screen

    int id;
    int slotNumber;

    // Display the available slots
    printf("Available slots:\n");
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 0) // If the slot is not reserved
        {
            printf("%d. %s\n", i + 1, slots[i].time);
        }
    }

    // Get the patient ID and desired slot from the admin
    printf("\nEnter the patient ID: ");

    while (1)
    {
        if (scanf("%d", &id) != 1 || id == 0) // Check if the entered ID is a non-zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a non-zero ID.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid ID is entered
        }
    }

    // Check if the patient exists
    int found = 0;
    struct Patient *current = head; // Pointer to traverse the linked list

    while (current != NULL)
    {
        if (current->id == id) // If the patient with the given ID is found
        {
            found = 1; // Patient exists
            break;
        }
        current = current->next; // Move to the next node
    }

    if (found == 0)
    {
        printf("\033[1;31m"); // Set color to red
        printf("Patient ID is not found.");
        printf("\033[0m"); // Reset color
        sleep(2);
        Admin_Window(); // Call the function to go back to the admin window
    }

    printf("Enter the number of the desired slot: ");

    while (1)
    {
        if (scanf("%d", &slotNumber) != 1) // Check if the entered ID is a non-zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid ID is entered
        }
    }

    // Check if the slot is available
    if (slotNumber < 1 || slotNumber > 5 || slots[slotNumber - 1].isReserved == 1)
    {
        printf("\033[1;31m"); // Set color to red
        printf("Invalid slot number! Please try again.\n");
        printf("\033[0m"); // Reset color

        sleep(2);
        system("cls"); // Clear the console screen
        reserveSlot(); // Call the function again to reserve a slot
    }

    // Reserve the slot
    slots[slotNumber - 1].isReserved = 1; // Mark the slot as reserved
    slots[slotNumber - 1].patientId = id; // Assign the patient ID to the slot
    printf("Slot reserved successfully.\n");
    sleep(2);

    Admin_Window(); // Call the function to go back to the admin window
}

void Cancel_Reservations()
{
    system("cls"); // Clear the console screen

    int id;
    printf("Enter the patient ID to cancel his reservation: ");
    while (1)
    {
        if (scanf("%d", &id) != 1 || id == 0) // Check if the entered number is an integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a valid ID.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid age is entered
        }
    }

    // Check each slot to see if it's reserved by the patient
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1 && slots[i].patientId == id) // If the slot is reserved by the patient
        {
            // Cancel the reservation
            slots[i].isReserved = 0; // Mark the slot as not reserved
            slots[i].patientId = 0;  // Remove the patient ID from the slot
            printf("Reservation for patient ID %d in slot %s has been cancelled.\n", id, slots[i].time);
            sleep(2);
            Admin_Window(); // Call the function to go back to the admin window
            return;
        }
    }

    // If we reach here, it means the patient didn't have any reservations
    printf("\033[1;31m"); // Set color to red
    printf("No reservations found for patient ID %d.\n", id);
    printf("\033[0m"); // Reset color
    sleep(2);
    Admin_Window(); // Call the function to go back to the admin window
}

void Print_Patients()
{
    struct Patient *current = head; // Pointer to traverse the linked list starting from the head
    while (current != NULL)         // Iterate until the end of the linked list is reached
    {
        printf("Name: %s, Age: %d, Gender: %c, ID: %d\n", current->name, current->age, current->gender, current->id);
        // Print the patient's name, age, gender, and ID using the printf function

        current = current->next; // Move to the next node in the linked list
    }
}

void Print_Reservations()
{
    printf("Reservations:\n"); // Print the heading for the reservations
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1) // If the slot is reserved
        {
            printf("Slot: %s, Patient ID: %d\n", slots[i].time, slots[i].patientId); // Print the slot time and patient ID
        }
    }
}

void User_Window()
{
    system("cls"); // Clear the console screen
    // print the menu:
    printf("Please choose an option:\n");
    printf("1. View patient record.\n");
    printf("2. View today's reservations.\n");
    printf("3. Back.\n");

    while (1) // Infinite loop to keep the user in the user window until they choose to go back
    {
        int choice = 0;

        // Get user input
        scanf("%d", &choice);
        clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // View patient record
            printf("View patient record selected.\n");
            sleep(1);
            View_Patient_Record(); // Call the function to view the patient record
            break;

        case 2:
            // View today's reservations
            printf("View today's reservations selected.\n");
            sleep(1);
            View_Todays_Reservations(); // Call the function to view today's reservations
            break;

        case 3:
            Welcome_Screen(); // Call the function to go back to the welcome screen
            break;

        default:
            printf("\033[1;31m"); // Set color to red
            printf("Invalid choice! Please choose a valid option.\n");
            printf("\033[0m"); // Reset color
            break;
        }
    }
}

void View_Patient_Record()
{
    system("cls"); // Clear the console screen

    int id;
    printf("Enter the patient ID: ");

    while (1)
    {
        if (scanf("%d", &id) != 1 || id == 0) // Check if the entered ID is a non-zero integer
        {
            printf("\033[1;31m"); // Set color to red
            printf("Invalid input. Please enter a non-zero ID.\n");
            printf("\033[0m");  // Reset color
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
        }
        else
        {
            clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input
            break;              // Exit the loop if a valid ID is entered
        }
    }

    // Find the patient with the given ID
    struct Patient *current = head; // Pointer to traverse the linked list starting from the head
    while (current != NULL)         // Iterate until the end of the linked list is reached
    {
        if (current->id == id) // If the current patient's ID matches the given ID
        {
            // Print the patient's information
            printf("Patient ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Gender: %c\n", current->gender);
            printf("\n");
            sleep(5);
            User_Window(); // Call the function to go back to the user window
            return;
        }
        current = current->next; // Move to the next node in the linked list
    }

    // If we reach here, it means no patient was found with the given ID
    printf("\033[1;31m"); // Set color to red
    printf("No patient found with ID %d.\n", id);
    printf("\033[0m"); // Reset color
    sleep(5);
    User_Window(); // Call the function to go back to the user window
}

void View_Todays_Reservations()
{
    system("cls"); // Clear the console screen

    printf("Today's Reservations:\n");
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1) // If the slot is reserved
        {
            printf("Slot: %s\n", slots[i].time);            // Print the slot time
            printf("Patient ID: %d\n", slots[i].patientId); // Print the patient ID
            printf("\n");
        }
    }

    sleep(5);
    User_Window(); // Call the function to go back to the user window
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) // Read characters from the input buffer until a newline character or end-of-file is encountered
    {
        // Do nothing with the characters, effectively discarding them
    }
}
