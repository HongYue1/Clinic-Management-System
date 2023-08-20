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
    system("cls");

    // Print a header
    printf("\033[1;32m"); // Set color to green //ANSI escape codes color
    printf("**********************************\n");
    printf("* Welcome to the Clinic System! *\n");
    printf("**********************************\n");
    printf("\033[0m");

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
        clearInputBuffer();

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // Admin Mode
            printf("Admin Mode selected\n");
            sleep(1);
            system("cls");
            if (login())
            {
                Admin_Window();
            };
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
        clearInputBuffer();

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
    // password is incorrect
    printf("\033[1;31m"); // Set color to red
    printf("Too many incorrect password attempts. Exiting the system...\n");
    printf("\033[0m"); // Reset color
    sleep(1);          // Delay for 1 second
    exit(0);           // Exit
}

void Admin_Window()
{
    system("cls");
    printf("Please choose an option:\n");
    printf("1. Add a new patient record.\n");
    printf("2. Edit patient record.\n");
    printf("3. Reserve a slot with the doctor\n");
    printf("4. Cancel reservation.\n");
    printf("5. Print all patients.\n");
    printf("6. Print all Reservations.\n");
    printf("7. Back.\n");

    while (1)
    {

        int choice = 0;

        // Get user input
        scanf("%d", &choice);
        clearInputBuffer();

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // Add a new patient record
            printf("New patient record selected.\n");
            sleep(1);
            Add_Patient_Window();
            break;

        case 2:
            // Edit a patient record.
            printf("Edit patient record selected.\n");
            sleep(1);
            Edit_Patient_Record();

            break;

        case 3:
            // Reserve a slot.
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

            while (1)
            {
                char e;
                fflush(stdin);

                scanf(" %c", &e);
                clearInputBuffer();
                if (e == 'e')
                {
                    system("cls");
                    Admin_Window();
                    break;
                }
            }

        case 6:
            // Print all Reservations
            printf("Print all Reservations selected.\n");
            sleep(1);
            Print_Reservations();
            sleep(1);
            printf("\nType (e) to go back when you are ready: ");

            while (1)
            {
                char e;
                fflush(stdin);

                scanf(" %c", &e);
                clearInputBuffer();
                if (e == 'e')
                {
                    system("cls");
                    Admin_Window();
                    break;
                }
            }

        case 7:
            // back option
            printf("Going back...\n");
            sleep(1);
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
    system("cls");

    char name[50];
    int age;
    char gender;
    int id;

    printf("Enter patient information:\n");
    printf("Name: ");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; /* fgets adds a \n charater to the end of the string,
This line removes the newline character from the string so not to cause a problem in printing.*/

    printf("Age: ");
    scanf("%d", &age);
    clearInputBuffer();

    printf("Gender (M or F): ");
    scanf(" %c", &gender);

    printf("ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    // Call the Add_Patient function
    Add_Patient(name, age, gender, id);
}

void Add_Patient(char name[], int age, char gender, int id)
{
    // Check if the ID already exists
    struct Patient *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            printf("\033[1;31m"); // Set color to red
            printf("ID already exists. Entry rejected.\n");
            printf("\033[0m"); // Reset color
            sleep(1);
            Add_Patient_Window();
        }
        current = current->next;
    }

    // Create a new patient node
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    strcpy(newPatient->name, name); // using strcpy to skip using array
    newPatient->age = age;
    newPatient->gender = gender;
    newPatient->id = id;
    newPatient->next = NULL;

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

    length++;

    printf("Patient added Successully!\n");
    sleep(1);
    Admin_Window();
}

void Edit_Patient_Record()
{
    system("cls");

    int id;
    printf("Enter the Patient ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    struct Patient *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            // The patient with the given ID is found, so now edit the information
            printf("Enter new patient information:\n");

            printf("Name: ");

            fflush(stdin);
            fgets(current->name, sizeof(current->name), stdin);
            current->name[strcspn(current->name, "\n")] = 0; // Remove the newline character

            printf("Age: ");
            scanf("%d", &(current->age));
            clearInputBuffer();

            printf("Gender (M or F): ");
            scanf(" %c", &(current->gender));

            printf("Patient record updated successfully.\n");
            sleep(1);

            Admin_Window();
        }
        current = current->next;
    }

    // If we reach here, it means the patient with the given ID was not found
    printf("\033[1;31m"); // Set color to red
    printf("Incorrect ID! No patient found with the given ID.\n");
    printf("\033[0m"); // Reset color
    sleep(2);

    Admin_Window();
}

void reserveSlot()
{
    system("cls");

    int id;
    int slotNumber;

    // Display the available slots
    printf("Available slots:\n");
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 0)
        {
            printf("%d. %s\n", i + 1, slots[i].time);
        }
    }

    // Get the patient ID and desired slot from the admin
    printf("\nEnter the patient ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    // check if the user exists.
    int found = 0;
    struct Patient *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            found = 1; // Patient exists
            break;
        }
        current = current->next;
    }

    if (found == 0)
    {
        printf("\033[1;31m"); // Set color to red
        printf("Patient ID is not found.");
        printf("\033[0m"); // Reset color
        sleep(2);
        Admin_Window();
    }

    printf("Enter the number of the desired slot: ");
    scanf("%d", &slotNumber);
    clearInputBuffer();

    // Check if the slot is available
    if (slotNumber < 1 || slotNumber > 5 || slots[slotNumber - 1].isReserved == 1)
    {
        printf("\033[1;31m"); // Set color to red
        printf("Invalid slot number! Please try again.\n");
        printf("\033[0m"); // Reset color

        sleep(2);
        system("cls");
        reserveSlot();
    }

    // Reserve the slot
    slots[slotNumber - 1].isReserved = 1; // Changed true to 1
    slots[slotNumber - 1].patientId = id;
    printf("Slot reserved successfully.\n");
    sleep(2);

    Admin_Window();
}

void Cancel_Reservations()
{
    system("cls");

    int id;
    printf("Enter the patient ID to cancel his reservation: ");
    scanf("%d", &id);
    clearInputBuffer();

    // Check each slot to see if it's reserved by the patient
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1 && slots[i].patientId == id)
        {
            // Cancel the reservation
            slots[i].isReserved = 0;
            slots[i].patientId = 0;
            printf("Reservation for patient ID %d in slot %s has been cancelled.\n", id, slots[i].time);
            sleep(2);
            Admin_Window();
            return;
        }
    }

    // If we reach here, it means the patient didn't have any reservations
    printf("\033[1;31m"); // Set color to red
    printf("No reservations found for patient ID %d.\n", id);
    printf("\033[0m"); // Reset color
    sleep(2);
    Admin_Window();
}

void Print_Reservations()
{
    printf("Reservations:\n");
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1)
        {
            printf("Slot: %s, Patient ID: %d\n", slots[i].time, slots[i].patientId);
        }
    }
}

void Print_Patients()
{
    struct Patient *current = head;
    while (current != NULL)
    {
        printf("Name: %s, Age: %d, Gender: %c, ID: %d\n", current->name, current->age, current->gender, current->id);
        current = current->next;
    }
}

void User_Window()
{
    system("cls");
    printf("Please choose an option:\n");
    printf("1. View patient record.\n");
    printf("2. View today's reservations.\n");
    printf("3. Back.\n");

    while (1)
    {
        int choice = 0;

        // Get user input
        scanf("%d", &choice);
        clearInputBuffer();

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            // View patient record
            printf("View patient record selected.\n");
            sleep(1);
            View_Patient_Record();
            break;
        case 2:
            // View today's reservations
            printf("View today's reservations selected.\n");
            sleep(1);
            View_Todays_Reservations();
            break;

        case 3:
            // back option
            printf("Going back...\n");
            sleep(1);
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

void View_Patient_Record()
{
    system("cls");

    int id;
    printf("Enter the patient ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    // Find the patient with the given ID
    struct Patient *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            // Print the patient's information
            printf("Patient ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Gender: %c\n", current->gender);
            printf("\n");
            sleep(3);
            User_Window();
            return;
        }
        current = current->next;
    }

    // If we reach here, it means no patient was found with the given ID
    printf("\033[1;31m"); // Set color to red
    printf("No patient found with ID %d.\n", id);
    printf("\033[0m"); // Reset color
    sleep(5);
    User_Window();
}

void View_Todays_Reservations()
{
    system("cls");

    printf("Today's Reservations:\n");
    for (int i = 0; i < 5; i++)
    {
        if (slots[i].isReserved == 1)
        {
            printf("Slot: %s\n", slots[i].time);
            printf("Patient ID: %d\n", slots[i].patientId);
            printf("\n");
        }
    }

    sleep(5);
    User_Window();
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}