# 🛒 C Console-Based Shopping Cart Management System

This project is a simple, command-line application developed in C to manage product inventory for a mock online shopping cart. It serves as an internal assessment project to demonstrate fundamental C programming concepts, including data structures, function modularity, array manipulation, and persistent file input/output (I/O).

# Key Features & C Concepts Demonstrated

The application adheres to all core project requirements, utilizing basic C functionalities and standard library features (stdio.h, stdlib.h).

Requirement

C Implementation

Function(s) Used

1. Data Structure

struct to define Product record.

typedef struct Product

2. Add Record

Unique ID validation and reading strings with spaces (%[^\n]).

addRecord()

3. Display Records

Looping through an array of structs.

displayAllRecords()

4. Search by ID

Pointers to return the address of the found struct.

findProductById()

5. Update Record

Modifying struct members via a pointer reference.

updateRecord()

6. Delete Record

Hard Deletion using array shifting (swapping method).

deleteRecord()

7. File Persistence

Reading and writing structured data to cart_data.txt.

loadFromFile(), writeToFile()

# How to Compile and Run

This project is a single-file C application and requires a standard C compiler (like GCC).

Save: Ensure the code is saved as ONLINE_SHOPPING_CART.c.

Compile: Open your terminal/command prompt and run:

gcc ONLINE_SHOPPING_CART.c -o cart_app


Run: Execute the compiled application:

./cart_app


# File I/O Mechanism

To successfully handle product names that contain spaces (e.g., "Smart Watch"), the application uses a pipe character (|) as a specialized delimiter for the string field in the data file (cart_data.txt). This prevents data corruption when loading records back into memory.

Writing (Saving Data): fprintf(file, "%d |%s| %.2f %d\n", ...)

Reading (Loading Data): fscanf(file, "%d |%49[^|]| %f %d\n", ...)

This pattern ensures data integrity across program executions, fulfilling the requirement for persistent record keeping.
