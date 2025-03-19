#include <stdio.h>  // For input and output operations
#include <stdlib.h> // For using inbuilt library functions
#include <string.h> // For using inbuilt string operations

#define MAX 100 // Maximum size of the queue is 100

// Structure to represent a patient
typedef struct 
{
    int id;
    char name[50];
    char issue[100];
    char dateOfAdmit[15]; // Date of admit
    int age;              // Patient's age
    char bloodGroup[5];   // Blood group
    char contactNo[15];   // Contact number
} Patient;

// Queue structure
typedef struct 
{
    Patient patients[MAX]; // Structure variable is declared with MAX size
    int front;
    int rear;
} Queue;

typedef struct Staff 
{
    char username[MAX];
    char password[MAX];
} Staff;

Staff staff = {"admin", "admin123"}; // Staff ID and password are set for Login purpose

// Function to initialize the queue
void create(Queue *q) 
{
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) 
{
    return q->front == -1;
}

// Function to check if the queue is full
int isFull(Queue *q) 
{
    return (q->rear + 1) % MAX == q->front;
}

// Function to add a patient to the queue
void enqueue(Queue *q, Patient p)
{
    if (isFull(q)) 
    {
        printf("Queue is full! Cannot add more patients data.\n");
        return;
    }
    if (isEmpty(q)) 
    {
        q->front = q->rear = 0;
    } 
    else 
    {
        q->rear = (q->rear + 1) % MAX;
    }
    q->patients[q->rear] = p;
    printf("Patient data added successfully.\n");
}

// Function to remove a patient from the queue
Patient dequeue(Queue *q) 
{
    Patient p;
    if (isEmpty(q)) 
    {
        printf("Queue is empty! No more patients to process.\n");
        p.id = -1; // Invalid ID to indicate no patient
        return p;
    }
    p = q->patients[q->front];
    if (q->front == q->rear) 
    {
        q->front = q->rear = -1; // Reset queue
    } 
    else 
    {
        q->front = (q->front + 1) % MAX;
    }
    return p;
}

// Function to display the queue
void display(Queue *q) 
{
    if (isEmpty(q)) 
    {
        printf("No patients in the queue.\n");
        return;
    }
    printf("Current Patients in the Queue are:\n");
    int i = q->front;
    while (1) 
    {
        Patient p = q->patients[i];
        printf("ID: %d\tName: %s\tIssue: %s\tDate of Admit: %s\tAge: %d\tBlood Group: %s\tContact No: %s\n",
               p.id, p.name, p.issue, p.dateOfAdmit, p.age, p.bloodGroup, p.contactNo);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
}

// Function to delete a specific patient record by ID
void deletePatient(Queue *q, int id) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty! No more patients data to delete.\n");
        return;
    }

    int found = 0;
    Queue tempQueue;
    create(&tempQueue);

    // Traverse the queue and transfer patients to a temporary queue, skipping the one to be deleted
    while (!isEmpty(q)) 
    {
        Patient current = dequeue(q);
        if (current.id == id) 
        {
            found = 1; // Mark that the patient is found
            printf("Patient with ID %d has been deleted.\n", id);
        } 
        else 
        {
            enqueue(&tempQueue, current); // Keep other patients in the temporary queue
        }
    }

    // Restore patients from the temporary queue back to the original queue
    while (!isEmpty(&tempQueue)) 
    {
        enqueue(q, dequeue(&tempQueue));
    }
    if (!found) 
    {
        printf("Patient with ID %d not found.\n", id);
    }
}

int authenticateStaff(const char *username, const char *password) 
{
    return strcmp(username, staff.username) == 0 && strcmp(password, staff.password) == 0;
}

void staffLogin() 
{
    char username[MAX], password[MAX];
    int choice;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    if (authenticateStaff(username, password)) 
    {
        printf("Login successful!\n");
    } 
    else 
    {
        printf("Invalid ID or password. Try again!\n");
        exit(0);
    }
}

int main() 
{
    Queue queue;
    create(&queue);
    int choice1;
    printf("\n--- Hospital Patient Management System ---\n");
    printf("1. Staff Login\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice1);
    switch (choice1) 
    {
    case 1:
        staffLogin();
        break;
    case 2:
        printf("Exiting....\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        exit(0);
    }

    int choice;
    while (1) 
    {
        printf("\n~Hospital Patient Management System~\n");
        printf("1. Add Patient\n");
        printf("2. Process the Next Patient\n");
        printf("3. Display All the Patient Records\n");
        printf("4. Delete Patient Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1: 
        {
            Patient p;
            printf("Enter Patient ID: ");
            scanf("%d", &p.id);
            printf("Enter Patient Name: ");
            scanf(" %[^\n]%*c", p.name);
            printf("Enter Patient Age: ");
            scanf("%d", &p.age);
            printf("Enter Contact Number: ");
            scanf(" %[^\n]%*c", p.contactNo);
            printf("Enter Patient Issue: ");
            scanf(" %[^\n]%*c", p.issue);
            printf("Enter Date of Admit (dd/mm/yyyy): ");
            scanf(" %[^\n]%*c", p.dateOfAdmit);
            enqueue(&queue, p);
            break;
        }
        case 2: 
            Patient p = dequeue(&queue);
            if (p.id != -1) 
            {
                printf("Processing Patient:\n");
                printf("ID: %d\t Name: %s\t Age: %d\t Contact No: %s\t Blood Group: %s\t Issue: %s\t Date of Admit: %s\n",
                       p.id, p.name, p.age, p.contactNo, p.bloodGroup, p.issue, p.dateOfAdmit);
            }
            break;
        case 3:
            display(&queue);
            break;
        case 4: 
            int id;
            printf("Enter the ID of the patient to delete: ");
            scanf("%d", &id);
            deletePatient(&queue, id);
            break;
        case 5:
            printf("Exiting the system.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}