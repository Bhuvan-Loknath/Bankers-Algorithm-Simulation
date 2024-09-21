#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

/* Global variables */
int available[NUMBER_OF_RESOURCES]; // Available resources
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; // Maximum demand of each customer
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; // Currently allocated resources
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; // Remaining needs of each customer

void initialize_resources(int argc, char *argv[]);
void read_maximum(char *filename);
int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);
void display_state();

int main(int argc, char *argv[]) {
    if (argc != NUMBER_OF_RESOURCES + 1) {
        printf("Usage: %s <resource_1> <resource_2> <resource_3> <resource_4>\n", argv[0]);
        return 1;
    }

    initialize_resources(argc, argv); // Initialize available resources
    read_maximum("maximum.txt"); // Read maximum requests from file

    printf("Welcome to the Banker's Algorithm Simulation\n\n");
    printf("Initializing system with resources:\n");
    printf("Available: ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("[%d] ", available[i]);
    }
    printf("\n\n");

    printf("Reading maximum request file...\n");
    printf("Maximum requests initialized:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Please enter commands:\n");
    printf("- 'RQ cust_num R1 R2 R3 R4' to request resources\n");
    printf("- 'RL cust_num R1 R2 R3 R4' to release resources\n");
    printf("- '*' to display the current values of the data structures\n");
    printf("- 'exit' to quit\n\n");

    char command[10];
    while (1) {
        printf("Command: ");
        scanf("%s", command);
        if (strcmp(command, "exit") == 0) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else if (strcmp(command, "*") == 0) {
            display_state(); // Display current system state
        } else {
            int customer_num;
            int resources[NUMBER_OF_RESOURCES];
            scanf("%d", &customer_num);
            for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
                scanf("%d", &resources[i]);
            }
            if (strcmp(command, "RQ") == 0) {
                request_resources(customer_num, resources); // Handle resource request
            } else if (strcmp(command, "RL") == 0) {
                release_resources(customer_num, resources); // Handle resource release
            }
        }
    }

    return 0;
}

/* Initialize resources passed by user */
void initialize_resources(int argc, char *argv[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = atoi(argv[i + 1]); // Store available resources
    }
}

/* Read maximum resources from file "maximum.txt" */
void read_maximum(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            fscanf(file, "%d,", &maximum[i][j]); // Read maximum requests
            allocation[i][j] = 0; // Initialize allocation to 0
            need[i][j] = maximum[i][j]; // Set need to maximum
        }
    }

    fclose(file);
}

/* Handle resource requests from customer */
int request_resources(int customer_num, int request[]) {
    printf("Requesting resources for Customer %d...\n", customer_num);

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > need[customer_num][i] || request[i] > available[i]) {
            printf("Request denied. Insufficient resources.\n");
            return -1; // Request denied
        }
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] -= request[i]; // Update available resources
        allocation[customer_num][i] += request[i]; // Update allocation
        need[customer_num][i] -= request[i]; // Update need
    }

    printf("Request granted. System is in a safe state.\n");
    return 0; // Request granted
}

/* Release resources allocated to customer */
void release_resources(int customer_num, int release[]) {
    printf("Releasing resources for Customer %d...\n", customer_num);

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (release[i] > allocation[customer_num][i]) {
            printf("Release denied. Exceeds allocated resources.\n");
            return; // Release denied
        }
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += release[i]; // Update available resources
        allocation[customer_num][i] -= release[i]; // Update allocation
        need[customer_num][i] += release[i]; // Update need
    }

    printf("Resources released successfully.\n");
}

/* Display the current state of the system */
void display_state() {
    printf("Current system state:\n");
    printf("Available: ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("[%d] ", available[i]); 
    }
    printf("\nMaximum:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", maximum[i][j]); 
        }
        printf("\n");
    }
    printf("Allocation:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", allocation[i][j]); 
        }
        printf("\n");
    }
    printf("Need:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", need[i][j]); 
        }
        printf("\n");
    }
    printf("\n");
}
