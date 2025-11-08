#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define NAME_LENGTH 50
#define DATA_FILE "cart_data.txt"

typedef struct Product
{
    int id;
    char name[NAME_LENGTH];
    float price;
    int quantity;
} Product;

Product inventory[MAX_PRODUCTS];
int product_count = 0;

void loadFromFile()
{
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        return;
    }
    
    Product p;

    while (fscanf(file, "%d |%49[^|]| %f %d\n", &p.id, p.name, &p.price, &p.quantity) == 4)
    {
        if (product_count < MAX_PRODUCTS)
        {
            inventory[product_count] = p;
            product_count++;
        }
    }

    fclose(file);
}

void writeToFile()
{
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL)
    {
        printf("Error writing to file.\n");
        return;
    }

    for (int i = 0; i < product_count; i++)
    {
        fprintf(file, "%d |%s| %.2f %d\n", 
                inventory[i].id, 
                inventory[i].name, 
                inventory[i].price, 
                inventory[i].quantity);
    }

    fclose(file);
    printf("Record saved to file successfully.\n");
}

Product *findProductById(int id)
{
    for (int i = 0; i < product_count; i++)
    {
        if (inventory[i].id == id)
        {
            return &inventory[i];
        }
    }
    return NULL;
}

void addRecord()
{
    if (product_count >= MAX_PRODUCTS)
    {
        printf("Inventory is full.\n");
        return;
    }

    Product new_product;
    int input_id;

    while (1)
    {
        printf("Enter Product ID: ");
        
        if (scanf("%d", &input_id) != 1 || input_id <= 0)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Enter a positive integer ID: ");
            continue;
        }
        
        if (findProductById(input_id) != NULL)
        {
            printf("Error: ID %d already exists. Enter a unique ID: ", input_id);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        new_product.id = input_id;
        break;
    }

    printf("Enter Product Name (including Spaces): ");
    scanf(" %49[^\n]", new_product.name);
    
    printf("Enter Price: ");
    while (scanf("%f", &new_product.price) != 1 || new_product.price <= 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid price. Enter a positive number: ");
    }

    printf("Enter Quantity: ");
    while (scanf("%d", &new_product.quantity) != 1 || new_product.quantity <= 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid quantity. Enter a positive integer: ");
    }

    inventory[product_count] = new_product;
    product_count++;
    printf("Product added successfully with ID: %d\n", new_product.id);
}

void displayRecord(Product *p)
{
    if (p == NULL)
    {
        printf("Product not found.\n");
        return;
    }
    printf("\n--- Product Details ---\n");
    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Price: %.2f\n", p->price);
    printf("Quantity: %d\n", p->quantity);
    printf("-----------------------\n");
}

void displayAllRecords()
{
    if (product_count == 0)
    {
        printf("No records found in inventory.\n");
        return;
    }
    
    printf("\n===================================================================================\n");
    printf("| ID         | Name                                   | Price         | Qty        |\n");
    printf("===================================================================================\n");
    for (int i = 0; i < product_count; i++)
    {
        printf("| %-10d | %-38s | %-13.2f | %-10d |\n", 
               inventory[i].id, 
               inventory[i].name, 
               inventory[i].price, 
               inventory[i].quantity);
    }
    printf("===================================================================================\n");
}

void searchById()
{
    int id;
    printf("Enter Product ID to search: ");
    if (scanf("%d", &id) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input.\n");
        return;
    }
    
    Product *found_product = findProductById(id);

    if (found_product != NULL)
    {
        displayRecord(found_product);
    }
    else
    {
        printf("Product with ID %d not found.\n", id);
    }
}

void updateRecord()
{
    int id;
    printf("Enter Product ID to update: ");
    if (scanf("%d", &id) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input.\n");
        return;
    }
    
    Product *p = findProductById(id);

    if (p != NULL)
    {
        printf("Updating record for ID %d (%s).\n", p->id, p->name);
        
        printf("Enter New Price (%.2f): ", p->price);
        float new_price;
        if (scanf("%f", &new_price) == 1 && new_price > 0)
        {
            p->price = new_price;
        }

        printf("Enter New Quantity (%d): ", p->quantity);
        int new_quantity;
        if (scanf("%d", &new_quantity) == 1 && new_quantity >= 0)
        {
            p->quantity = new_quantity;
        }

        printf("Record updated successfully.\n");
    }
    else
    {
        printf("Product with ID %d not found. Update failed.\n", id);
    }
}

void deleteRecord()
{
    int id;
    printf("Enter Product ID to delete: ");
    if (scanf("%d", &id) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input.\n");
        return;
    }

    int found_index = -1;
    for (int i = 0; i < product_count; i++)
    {
        if (inventory[i].id == id)
        {
            found_index = i;
            break;
        }
    }

    if (found_index != -1)
    {
        for (int i = found_index; i < product_count - 1; i++)
        {
            inventory[i] = inventory[i + 1];
        }
        product_count--;
        printf("Record for ID %d deleted successfully.\n", id);
    }
    else
    {
        printf("Product with ID %d not found. Deletion failed.\n", id);
    }
}

void displayMenu()
{
    printf("\n--- Online Shopping Cart Management ---\n");
    printf("1. Add Product Record\n");
    printf("2. Display All Records\n");
    printf("3. Search Record by ID\n");
    printf("4. Update Existing Record\n");
    printf("5. Delete Record\n");
    printf("6. Save & Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    loadFromFile();
    
    int choice;
    do
    {
        displayMenu();
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choice = 0;
            printf("\nInvalid input. Please enter a number.\n");
        }
        
        switch (choice)
        {
            case 1:
                addRecord();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                searchById();
                break;
            case 4:
                updateRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                writeToFile();
                printf("Exiting application.\n");
                break;
            default:
                if (choice != 6)
                {
                    printf("Invalid choice. Please try again.\n");
                }
                break;
        }
    } while (choice != 6);
    
    return 0;
}
