#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEDICINE_FILE "medicines.dat"
#define PRESCRIPTION_FILE "prescriptions.dat"
#define SALES_FILE "sales.dat"

typedef struct
{
    char name[100];
    float price;
    int quantity;
} Medicine;

typedef struct
{
    char patientName[100];
    char medicineName[100];
    int quantity;
} Prescription;

typedef struct
{
    char medicineName[100];
    int quantity;
    float totalCost;
} Sale;

void displayMenu();
void addMedicine();
void listMedicines();
void addPrescription();
void listPrescriptions();
void updatePrescription();
void processSale();
void listSales();
void generateReport();
void searchMedicine();
void searchPrescription();

int main()
{
    int choice;

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
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
            processSale();
            break;
        case 7:
            listSales();
            break;
        case 8:
            generateReport();
            break;
        case 9:
            searchMedicine();
            break;
        case 10:
            searchPrescription();
            break;
        case 11:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 11);

    return 0;
}

void displayMenu()
{
    printf("\n--- Pharmacy Management System ---\n");
    printf("1. Add Medicine\n");
    printf("2. List Medicines\n");
    printf("3. Add Prescription\n");
    printf("4. List Prescriptions\n");
    printf("5. Update Prescription\n");
    printf("6. Process Sale\n");
    printf("7. List Sales\n");
    printf("8. Generate Report\n");
    printf("9. Search Medicine\n");
    printf("10. Search Prescription\n");
    printf("11. Exit\n");
}

void addMedicine()
{
    FILE *file = fopen(MEDICINE_FILE, "a");
    if (file == NULL)
    {
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

void listMedicines()
{
    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening medicine file");
        return;
    }

    Medicine med;

    printf("\n--- List of Medicines ---\n");
    while (fscanf(file, "%s %f %d", med.name, &med.price, &med.quantity) != EOF)
    {
        printf("Name: %s\nPrice: %.2f\nQuantity: %d\n\n", med.name, med.price, med.quantity);
    }
    fclose(file);
}

void addPrescription()
{
    FILE *file = fopen(PRESCRIPTION_FILE, "a");
    if (file == NULL)
    {
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

void listPrescriptions()
{
    FILE *file = fopen(PRESCRIPTION_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening prescription file");
        return;
    }

    Prescription pres;

    printf("\n--- List of Prescriptions ---\n");
    while (fscanf(file, "%s %s %d", pres.patientName, pres.medicineName, &pres.quantity) != EOF)
    {
        printf("Patient: %s\nMedicine: %s\nQuantity: %d\n\n", pres.patientName, pres.medicineName, pres.quantity);
    }
    fclose(file);
}

void updatePrescription()
{
    FILE *file = fopen(PRESCRIPTION_FILE, "r+");
    if (file == NULL)
    {
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

    while (fscanf(file, "%s %s %d", patientName, medicineName, &quantity) != EOF)
    {
        if (strcmp(patientName, patientName) == 0 && strcmp(medicineName, medicineName) == 0)
        {
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

    if (!found)
    {
        printf("Prescription not found.\n");
    }

    fclose(file);
}

void processSale()
{
    FILE *medFile = fopen(MEDICINE_FILE, "r+");
    FILE *saleFile = fopen(SALES_FILE, "a");
    if (medFile == NULL || saleFile == NULL)
    {
        perror("Error opening files");
        return;
    }

    Medicine med;
    Sale sale;
    char medName[100];
    int quantity;

    printf("Enter medicine name for sale: ");
    fgets(medName, sizeof(medName), stdin);
    medName[strcspn(medName, "\n")] = '\0';

    printf("Enter quantity to sell: ");
    scanf("%d", &quantity);
    getchar();

    rewind(medFile);
    while (fscanf(medFile, "%s %f %d", med.name, &med.price, &med.quantity) != EOF)
    {
        if (strcmp(med.name, medName) == 0)
        {
            if (med.quantity >= quantity)
            {
                med.quantity -= quantity;
                sale.quantity = quantity;
                sale.totalCost = quantity * med.price;
                strcpy(sale.medicineName, medName);

                fprintf(saleFile, "%s %d %.2f\n", sale.medicineName, sale.quantity, sale.totalCost);
                fseek(medFile, -((long)strlen(med.name) + sizeof(float) + sizeof(int) + 3), SEEK_CUR);
                fprintf(medFile, "%s %.2f %d\n", med.name, med.price, med.quantity);
                printf("Sale processed successfully.\n");
            }
            else
            {
                printf("Insufficient quantity in inventory.\n");
            }
            break;
        }
    }

    fclose(medFile);
    fclose(saleFile);
}

void listSales()
{
    FILE *file = fopen(SALES_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening sales file");
        return;
    }

    Sale sale;

    printf("\n--- List of Sales ---\n");
    while (fscanf(file, "%s %d %f", sale.medicineName, &sale.quantity, &sale.totalCost) != EOF)
    {
        printf("Medicine: %s\nQuantity: %d\nTotal Cost: %.2f\n\n", sale.medicineName, sale.quantity, sale.totalCost);
    }
    fclose(file);
}

void generateReport()
{
    FILE *medFile = fopen(MEDICINE_FILE, "r");
    FILE *saleFile = fopen(SALES_FILE, "r");
    FILE *presFile = fopen(PRESCRIPTION_FILE, "r");
    if (medFile == NULL || saleFile == NULL || presFile == NULL)
    {
        perror("Error opening report files");
        return;
    }

    Medicine med;
    Sale sale;
    Prescription pres;
    float totalSales = 0;
    int totalPrescriptions = 0;

    printf("\n--- Inventory Status Report ---\n");
    while (fscanf(medFile, "%s %f %d", med.name,
                  &med.price, &med.quantity) != EOF)
    {
        printf("Medicine: %s\nPrice: %.2f\nQuantity: %d\n\n", med.name, med.price, med.quantity);
    }

    printf("\n--- Sales Report ---\n");
    while (fscanf(saleFile, "%s %d %f", sale.medicineName, &sale.quantity, &sale.totalCost) != EOF)
    {
        printf("Medicine: %s\nQuantity: %d\nTotal Cost: %.2f\n\n", sale.medicineName, sale.quantity, sale.totalCost);
        totalSales += sale.totalCost;
    }
    printf("Total Sales: %.2f\n", totalSales);

    printf("\n--- Prescription Report ---\n");
    while (fscanf(presFile, "%s %s %d", pres.patientName, pres.medicineName, &pres.quantity) != EOF)
    {
        printf("Patient: %s\nMedicine: %s\nQuantity: %d\n\n", pres.patientName, pres.medicineName, pres.quantity);
        totalPrescriptions++;
    }
    printf("Total Prescriptions: %d\n", totalPrescriptions);

    fclose(medFile);
    fclose(saleFile);
    fclose(presFile);
}

void searchMedicine()
{
    FILE *file = fopen(MEDICINE_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening medicine file");
        return;
    }
    Medicine med;
    char medName[100];
    int found = 0;

    printf("Enter medicine name to search: ");
    fgets(medName, sizeof(medName), stdin);
    medName[strcspn(medName, "\n")] = '\0';

    while (fscanf(file, "%s %f %d", med.name, &med.price, &med.quantity) != EOF)
    {
        if (strcmp(med.name, medName) == 0)
        {
            printf("Medicine found:\nName: %s\nPrice: %.2f\nQuantity: %d\n", med.name, med.price, med.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Medicine not found.\n");
    }

    fclose(file);
}

void searchPrescription()
{
    FILE *file = fopen(PRESCRIPTION_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening prescription file");
        return;
    }
    Prescription pres;
    char patientName[100];
    int found = 0;

    printf("Enter patient name to search: ");
    fgets(patientName, sizeof(patientName), stdin);
    patientName[strcspn(patientName, "\n")] = '\0';

    while (fscanf(file, "%s %s %d", pres.patientName, pres.medicineName, &pres.quantity) != EOF)
    {
        if (strcmp(pres.patientName, patientName) == 0)
        {
            printf("Prescription found:\nPatient: %s\nMedicine: %s\nQuantity: %d\n", pres.patientName, pres.medicineName, pres.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Prescription not found.\n");
    }

    fclose(file);
}