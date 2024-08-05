#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEDICINE_FILE "medicines.dat"
#define PRESCRIPTION_FILE "prescriptions.dat"

typedef struct {
    char name[100];
    float price;
    int quantity;
} Medicine;

typedef struct {
    char patientName[100];
    char medicineName[100];
    int quantity;
} Prescription;

void displayMenu();
void addMedicine();
void listMedicines();
void addPrescription();
void listPrescriptions();
void updatePrescription();

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
                updatePrescription();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    printf("\n--- Pharmacy Management System ---\n");
    printf("1. Add Medicine\n");
    printf("2. List Medicines\n");
    printf("3. Add Prescription\n");
    printf("4. List Prescriptions\n");
    printf("5. Update Prescription\n");
    printf("6. Exit\n");
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

void addPrescription() {
    FILE *file = fopen(PRESCRIPTION_FILE, "a");
    if (file == NULL) {
        perror("Error opening prescription file");
        return;
    }

    Prescription pres;

    printf("Enter patient name: ");
    fgets(pres.patientName, sizeof(pres.patientName), stdin);
    pres.patientName[strcspn(pres.patientName, "\n")] = '\0';

    printf("Enter prescribed medicine name: ");
    fgets(pres.medicineName, sizeof(pres.medicineName), stdin);
    pres.medicineName[strcspn(pres.medicineName, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &pres.quantity);
    getchar();

    fprintf(file, "%s %s %d\n", pres.patientName, pres.medicineName, pres.quantity);
    fclose(file);
    printf("Prescription added successfully.\n");
}

void listPrescriptions() {
    FILE *file = fopen(PRESCRIPTION_FILE, "r");
    if (file == NULL) {
        perror("Error opening prescription file");
        return;
    }

    Prescription pres;

    printf("\n--- List of Prescriptions ---\n");
    while (fscanf(file, "%[^\n] %[^\n] %d\n", pres.patientName, pres.medicineName, &pres.quantity) != EOF) {
        printf("Patient: %s\nMedicine: %s\nQuantity: %d\n\n", pres.patientName, pres.medicineName, pres.quantity);
    }
    fclose(file);
}

void updatePrescription() {
    FILE *file = fopen(PRESCRIPTION_FILE, "r+");
    if (file == NULL) {
        perror("Error opening prescription file");
        return;
    }

    char patientName[100];
    char medicineName[100];
    int quantity;
    int found = 0;

    printf("Enter patient name to update: ");
    fgets(patientName, sizeof(patientName), stdin);
    patientName[strcspn(patientName, "\n")] = '\0';

    printf("Enter prescribed medicine name to update: ");
    fgets(medicineName, sizeof(medicineName), stdin);
    medicineName[strcspn(medicineName, "\n")] = '\0';

    while (fscanf(file, "%[^\n] %[^\n] %d\n", patientName, medicineName, &quantity) != EOF) {
        if (strcmp(patientName, patientName) == 0 && strcmp(medicineName, medicineName) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &quantity);
            getchar();

            fseek(file, -((long)strlen(patientName) + (long)strlen(medicineName) + sizeof(int) + 3), SEEK_CUR);
            fprintf(file, "%s %s %d\n", patientName, medicineName, quantity);
            fflush(file);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Prescription not found.\n");
    }

    fclose(file);
}
