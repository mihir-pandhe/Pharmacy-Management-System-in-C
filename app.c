#include <stdio.h>
#include <stdlib.h>

#define MEDICINE_FILE "medicines.dat"
#define PRESCRIPTION_FILE "prescriptions.dat"

void displayMenu();
void addMedicine();
void listMedicines();
void addPrescription();
void listPrescriptions();

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
                addPrescription();
                break;
            case 4:
                listPrescriptions();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n--- Pharmacy Management System ---\n");
    printf("1. Add Medicine\n");
    printf("2. List Medicines\n");
    printf("3. Add Prescription\n");
    printf("4. List Prescriptions\n");
    printf("5. Exit\n");
}

void addMedicine() {
    FILE *file = fopen(MEDICINE_FILE, "a");
    if (file == NULL) {
        perror("Error opening medicine file");
        return;
    }

    char name[100];
    float price;
    
    printf("Enter medicine name: ");
    fgets(name, sizeof(name), stdin);
    printf("Enter medicine price: ");
    scanf("%f", &price);
    getchar();

    fprintf(file, "%s%.2f\n", name, price);
    fclose(file);
    printf("Medicine added successfully.\n");
}

void listMedicines() {
    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file == NULL) {
        perror("Error opening medicine file");
        return;
    }

    char name[100];
    float price;

    printf("\n--- List of Medicines ---\n");
    while (fscanf(file, "%[^\n] %f\n", name, &price) != EOF) {
        printf("Name: %s Price: %.2f\n", name, price);
    }
    fclose(file);
}

void addPrescription() {
    FILE *file = fopen(PRESCRIPTION_FILE, "a");
    if (file == NULL) {
        perror("Error opening prescription file");
        return;
    }

    char patientName[100];
    char medicineName[100];

    printf("Enter patient name: ");
    fgets(patientName, sizeof(patientName), stdin);
    printf("Enter prescribed medicine name: ");
    fgets(medicineName, sizeof(medicineName), stdin);

    fprintf(file, "%s%s\n", patientName, medicineName);
    fclose(file);
    printf("Prescription added successfully.\n");
}

void listPrescriptions() {
    FILE *file = fopen(PRESCRIPTION_FILE, "r");
    if (file == NULL) {
        perror("Error opening prescription file");
        return;
    }

    char patientName[100];
    char medicineName[100];

    printf("\n--- List of Prescriptions ---\n");
    while (fscanf(file, "%[^\n] %[^\n]\n", patientName, medicineName) != EOF) {
        printf("Patient: %s Medicine: %s\n", patientName, medicineName);
    }
    fclose(file);
}
