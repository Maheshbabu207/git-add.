#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"



void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    if(addressBook->contactCount==0)
    {
        populateAddressBook(addressBook);
    }
    
    // Load contacts from file during initialization (After files)
}
void loadContactsFromFile(AddressBook *addressBook)
{
    char name[50], mobile[20], email[20];
    FILE *file=fopen("contactlist.csv", "r");
    if(file==NULL)
    {
        printf("Error opening file to save contacts.\n");
        return;
    }
    while((fscanf(file, "%49[^,],%19[^,],%49[^\n]\n",name,mobile,email))==3)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name,name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);

        addressBook->contactCount++;

    }
    fclose(file);
}
void listContacts(AddressBook *addressBook)
{
    
    if (addressBook->contactCount == 0)
    {
        printf("There are no contacts in address book to display.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Contact %d: %s, %s, %s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}
void createContact(AddressBook *addressBook)
{
    char duplicatename[50];
    char mobile[30];
    char mail[50];
    int ret, retmail;
    printf("Enter the name : ");
    scanf(" %49[^\n]", duplicatename);
    getchar();
    strcpy(addressBook->contacts[addressBook->contactCount].name, duplicatename);
    printf("Enter the mobile number : ");
    scanf("%19[^\n]", mobile);
    getchar();
    do
    {
        ret = validate_mobilenumber(mobile,addressBook);
        if(ret)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
        }
        else
        {
            printf("Re-Enter mobile number: ");
            scanf("%19[^\n]", mobile);
            getchar();
        }
    }while(ret!=1);
    printf("Enter the mail id : ");
    scanf(" %49[^\n]", mail);
    getchar();
    do
    {
        retmail = validate_emailid(mail, addressBook);
        if(retmail)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
        }
        else
        {
            printf("Enter the mailid : ");
            scanf(" %49[^\n]",mail);
            getchar();
        }
    }while(retmail!=1);
    
    addressBook->contactCount++;
}

int validate_mobilenumber(char *mobile, AddressBook *addressBook)
{
    int i, len;
    len = strlen(mobile);
    if(len == 10)
    {
        for(i = 0; i < len; i++)
        {
            if(mobile[i] >= '0' && mobile[i] <= '9')
            {

            }
            else
            {
                printf("Invalid mobile number\n");
                return 0;
            }
        }
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, mobile)==0)
            {
                printf("Mobile number already exists\n");
                return 0;
            }
        }
        return 1;
    }
    else
    {
        printf("Invalid Mobile number\n");
        return 0;
    }
}
int validate_emailid(char *mail,AddressBook *addressBook)
{
    int count = 0, i;
    for(i = 0; mail[i]!='\0'; i++)
    {
        if(mail[i]=='@')
        {
            count++;
        }
    }
    if(count!=1)
    {
        printf("Inavalid input,@ not found in email\n");
        return 0;
    }
    char *dot = strchr(mail, '.');
    if(dot == NULL)
    {
        printf("Invalid input,Email contains '.'\n");
        return 0;
    }
    for(i = 0; mail[i]!='\0'; i++)
    {
        if(mail[i]==' ')
        {
            printf("Inavlid input, Email contain a space\n");
            return 0;
        }
    }
    int lettercount = 0;
    for(i = 0; mail[i]!='@'; i++)
    {
        lettercount++;
    }
    if(lettercount == 0)
    {
        printf("Invalid input, email consists some letters before @");
        return 0;
    }
    for(i = 0; mail[i]!='\0'; i++)
    {
        if(mail[i] >= 'A' && mail[i] <= 'Z')
        {
            return 0;
        }
    }
    if(strstr(mail, ".com")==NULL)
    {
        return 0;
    }
    return 1;
}

void searchContact(AddressBook *addressBook)
{
    int search, i;
    char searchname[50], searchmobile[30], searchmail[50];
    printf("\n1.Search by name\n2.Search by mobilenumber\n3.Search by Emailid:\n");
    scanf("%d",&search);
    getchar();
    switch(search)
    {
    case 1:
    {
        int flag = 0;
        printf("Enter the name for search :");
        scanf(" %49[^\n]", searchname);
        getchar();
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if((strstr(addressBook->contacts[i].name, searchname)) != NULL)
            {
                flag = 1;
                printf("\ncontacts found\n Name:%s Phone:%s Emailid:%s", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }
        if(flag==0)
        {
            printf("Contacts not found\n");
        }
    }
    break;
    case 2:
    {
        printf("Enter the mobile number for search :");
        scanf(" %19[^\n]", searchmobile);
        getchar();
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if((strstr(addressBook->contacts[i].phone, searchmobile))!=NULL)
            {
                printf("\n Contact found\n Name:%s phone:%s Emailid:%s",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }
        if(i == addressBook->contactCount)
        {
            printf("Contact not found\n");
        }
    }
    break;
    case 3:
    {
        printf("ENter the Emailid for search :");
        scanf(" %49[^\n]", searchmail);
        getchar();
        for(i = 0; i < addressBook->contactCount; i++);
        {
            if((strstr(addressBook->contacts[i].email,searchmail))!=NULL)
            {
                printf("\n Contact found\n Name:%s phone:%s Emailid:%s",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }
        printf("Contact not found\n");
    }
    break;
    }
}
void editContact(AddressBook *addressBook)
{
    int search, i;
    char searchname[50], searchmobile[30], searchmail[50];
    printf("\n1. Edit by name\n2. Edit by mobile number\n3. Edit by Email id:\n");
    scanf("%d", &search);
    getchar();
    int contactIndex = -1;
    switch(search)
    {
    case 1:
        printf("Enter the name to search: ");
        scanf(" %49[^\n]", searchname);
        getchar();

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].name, searchname)) 
            {
                contactIndex = i; 
                break;
            }
        }

        if(contactIndex == -1)
        {
            printf("Contact not found.\n");
            return;
        }
        break;

    case 2:
        printf("Enter the mobile number to search: ");
        scanf(" %19[^\n]", searchmobile);
        getchar();

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].phone, searchmobile)) 
            {
                contactIndex = i; 
            }
        }

        if(contactIndex == -1)
        {
            printf("Contact not found.\n");
            return;
        }
        break;

    case 3:
        printf("Enter the email to search: ");
        scanf(" %49[^\n]", searchmail);
        getchar();

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].email, searchmail)) 
            {
                contactIndex = i; 
                break;
            }
        }

        if(contactIndex == -1)
        {
            printf("Contact not found.\n");
            return;
        }
        break;

    default:
        printf("Invalid choice.\n");
        return;
    }
    Contact *contactToEdit = &addressBook->contacts[contactIndex];
    char newName[50], newPhone[30], newEmail[50];
    printf("Editing contact: %s, %s, %s\n", contactToEdit->name, contactToEdit->phone, contactToEdit->email);
    printf("Enter new name (or press Enter to keep it unchanged): ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0; 
    if (strlen(newName) > 0)
    {
        strcpy(contactToEdit->name, newName);
    }
    do
    {
        printf("Enter new phone number (10 digits): ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = 0; 

        int ret = validate_mobilenumber(newPhone, addressBook);
        if (ret)
        {
            strcpy(contactToEdit->phone, newPhone);
            break;
        }
        else
        {
            printf("Invalid phone number or phone already exists. Try again.\n");
        }
    } while (1);
    do
    {
        printf("Enter new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;
        int retmail = validate_emailid(newEmail, addressBook);
        if (retmail)
        {
            strcpy(contactToEdit->email, newEmail);
            break;
        }
        else
        {
            printf("Invalid email address. Try again.\n");
        }
    } while (1);

    printf("Contact updated successfully!\n");
}
void deleteContact(AddressBook *addressBook) 
{
    int searchChoice, i;
    char searchName[50], searchMobile[30], searchEmail[50];
    int contactIndex = -1;
    printf("\n1. Delete by name\n2. Delete by mobile number\n3. Delete by email id:\n");
    scanf("%d", &searchChoice);
    getchar(); 
    switch (searchChoice) 
    {
        case 1:
            printf("Enter the name of the contact to delete: ");
            scanf(" %49[^\n]", searchName);
            getchar();  
            for (i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, searchName) != NULL) 
                {
                    contactIndex = i;
                    break;
                }
            }
            break;

        case 2:
            printf("Enter the mobile number of the contact to delete: ");
            scanf(" %19[^\n]", searchMobile);
            getchar(); 
            for (i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].phone, searchMobile) != NULL) 
                {
                    contactIndex = i;
                    break;
                }
            }
            break;

        case 3:
            printf("Enter the email of the contact to delete: ");
            scanf(" %49[^\n]", searchEmail);
            getchar();
            for (i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].email, searchEmail) != NULL) 
                {
                    contactIndex = i;
                    break;
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }
    if (contactIndex == -1) 
    {
        printf("Contact not found.\n");
        return;
    }
    for (i = contactIndex; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "w");
    if (file==NULL)
    {
        printf("Error opening file to save contacts.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
      //  printf("mahesh");
        Contact *c = &addressBook->contacts[i];
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(file);
    printf("Your contacts have been saved successfully.\n");
}
