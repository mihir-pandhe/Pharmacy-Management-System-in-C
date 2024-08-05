#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEDICINE_FILE "medicines.dat"

typedef struct {
    char name[100];
    float price;
    int quantity;
} Medicine;

void displayMenu();
void addMedicine();
void listMedicines();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                listMedicines();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

void displayMenu() {
    printf("\n--- Pharmacy Management System ---\n");
    printf("1. Add Medicine\n");
    printf("2. List Medicines\n");
    printf("3. Exit\n");
}

void addMedicine() {
    FILE *file = fopen(MEDICINE_FILE, "a");
    if (file == NULL) {
        perror("Error opening medicine file");
        return;
    }

    Medicine med;

    printf("Enter medicine name: ");
    fgets(med.name, sizeof(med.name), stdin);
    med.name[strcspn(med.name, "\n")] = '\0';

    printf("Enter medicine price: ");
    scanf("%f", &med.price);
    getchar();

    printf("Enter medicine quantity: ");
    scanf("%d", &med.quantity);
    getchar();

    fprintf(file, "%s %.2f %d\n", med.name, med.price, med.quantity);
    fclose(file);
    printf("Medicine added successfully.\n");
}

void listMedicines() {
    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file == NULL) {
        perror("Error opening medicine file");
        return;
    }

    Medicine med;

    printf("\n--- List of Medicines ---\n");
    while (fscanf(file, "%[^\n] %f %d\n", med.name, &med.price, &med.quantity) != EOF) {
        printf("Name: %s\nPrice: %.2f\nQuantity: %d\n\n", med.name, med.price, med.quantity);
    }
    fclose(file);
}
