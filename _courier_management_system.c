#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct for a courier record
struct Courier {
    char name[50];
    char address[100];
    char phone[20];
    char trackingNo[20];
    float weight;
    char status[20];
};

// Function to add a new courier record
void addCourier() {
    struct Courier courier;
    FILE *file = fopen("couriers.txt", "ab");

    printf("Enter name: ");
    scanf(" %[^\n]", courier.name);

    printf("Enter address: ");
    scanf(" %[^\n]", courier.address);

    printf("Enter phone number: ");
    scanf(" %[^\n]", courier.phone);

    printf("Enter tracking number: ");
    scanf(" %[^\n]", courier.trackingNo);

    printf("Enter weight: ");
    scanf("%f", &courier.weight);

    printf("Enter status: ");
    scanf(" %[^\n]", courier.status);

    fwrite(&courier, sizeof(struct Courier), 1, file);
    fclose(file);
    printf("\nCourier added successfully!\n");
}





// Function to search for a courier record
void searchCourier() {
    struct Courier courier;
    char searchQuery[20];

    printf("Enter tracking number to search: ");
    scanf("%s", searchQuery);

    FILE *file = fopen("couriers.txt", "rb");
    int found = 0;

    while (fread(&courier, sizeof(struct Courier), 1, file)) {
        if (strcmp(courier.trackingNo, searchQuery) == 0) {
            found = 1;
            printf("\nCourier details:\n");
            printf("Name: %s\n", courier.name);
            printf("Address: %s\n", courier.address);
            printf("Phone number: %s\n", courier.phone);
            printf("Tracking number: %s\n", courier.trackingNo);
            printf("Weight: %.2f\n", courier.weight);
            printf("Status: %s\n\n", courier.status);
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("No courier found with tracking number: %s\n\n", searchQuery);
    }
}

// Function to update the status of a courier record
void updateCourier() {
    struct Courier courier;
    char searchQuery[20];

    printf("Enter tracking number to update status: ");
    scanf("%s", searchQuery);

    FILE *file = fopen("couriers.txt", "r+b");
    int found = 0;

    while (fread(&courier, sizeof(struct Courier), 1, file)) {
        if (strcmp(courier.trackingNo, searchQuery) == 0) {
            found = 1;
            printf("\nEnter new status: ");
            scanf("%s", courier.status);
            fseek(file, -sizeof(struct Courier), SEEK_CUR);
            fwrite(&courier, sizeof(struct Courier), 1, file);
            printf("\nStatus updated successfully!\n");
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("No courier found with tracking number: %s\n\n", searchQuery);
    }
}

// Function to delete a courier record
void deleteCourier() {
    struct Courier courier;
    char searchQuery[20];

    printf("Enter tracking number to delete: ");
    scanf("%s", searchQuery);

    FILE *file = fopen("couriers.txt", "rb");
    FILE *tempFile = fopen("temp.txt", "wb");
    int found = 0;

    while (fread(&courier, sizeof(struct Courier), 1, file)) {
        if (strcmp(courier.trackingNo, searchQuery) == 0) {
            found = 1;
            printf("\nCourier details:\n");
            printf("Name: %s\n", courier.name);
            printf("Address: %s\n", courier.address);
            printf("Phone number: %s\n", courier.phone);
            printf("Tracking number: %s\n", courier.trackingNo);
            printf("Weight: %.2f\n", courier.weight);
            printf("Status: %s\n\n", courier.status);
            continue;
        }
        fwrite(&courier, sizeof(struct Courier), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("No courier found with tracking number: %s\n\n", searchQuery);
    } else {
        remove("couriers.txt");
        rename("temp.txt", "couriers.txt");
        printf("Courier deleted successfully!\n\n");
    }
}
// Function to display all courier records
void displayCouriers() {
    struct Courier courier;

    FILE *file = fopen("couriers.txt", "rb");
    int count = 0;

    printf("\nAll courier records:\n");
    printf("====================\n");

    while (fread(&courier, sizeof(struct Courier), 1, file)) {
        printf("Name: %s\n", courier.name);
        printf("Address: %s\n", courier.address);
        printf("Phone number: %s\n", courier.phone);
        printf("Tracking number: %s\n", courier.trackingNo);
        printf("Weight: %.2f\n", courier.weight);
        printf("Status: %s\n\n", courier.status);
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("No courier records found.\n\n");
    }
}



int main() {
    int option;

    do {
        printf("Select an option:\n");
        printf("1. Add a new courier record\n");
        printf("2. Search for a courier record\n");
        printf("3. Update the status of a courier record\n");
        printf("4. Delete a courier record\n");
        printf("5. Display all the details\n");
        printf("6. Exit\n");

        scanf("%d", &option);

        switch(option) {
            case 1:
                addCourier();
                break;
            case 2:
                searchCourier();
                break;
            case 3:
                updateCourier();
                break;
            case 4:
                deleteCourier();
                break;
            case 5:
                displayCouriers();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option. Please select again.\n");
        }

    } while (option != 6);

    return 0;
}
