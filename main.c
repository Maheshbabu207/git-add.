#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Delete contact\n");
        printf("4. Edit contact\n");
        printf("5. Display contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        //  printf("Enter your choice:\n1.Create contact\n2.Search contact\n3.Delete contact\n4.Edit contact\n5.Display contacts\n6.Save contacts\n7.Exit");
        scanf(" %d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            deleteContact(&addressBook);
            break;
        case 4:
            editContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            saveContactsToFile(&addressBook);
            break;
        case 7:
            printf("Saving and Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
