#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)      //check if contacts are present else retyrn to main menu
    {
        printf("\nNo contacts to display\n");   //display output
        return;
    }

    switch( sortCriteria)       //switch-case to sort based on names/email/phone
    {
        case 1: //sort by name
        for ( int i = 0; i < addressBook->contactCount - 1; i++)        //bubble sort all contacts in AddressBook
        {
            for( int j = i+1; j < addressBook->contactCount; j++)
            {
                if(strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name)>0)  //strcmp to find lexicographiclly largest/smallest
                {
                    Contact temp = addressBook->contacts[i];            //swap contacts using temp variable
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }

        break;

        case 2://sort by phone
         for (int i = 0; i < addressBook->contactCount - 1; i++)        //bubble sort all contacts in AddressBook based on phone
            {
                for (int j = i + 1; j < addressBook->contactCount; j++)
                {
                    if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0)
                    {
                        Contact temp = addressBook->contacts[i];        //swap using temp variable
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;

            case 3: // Sort by email
            for (int i = 0; i < addressBook->contactCount - 1; i++)     //bubble sort all contacts in AddressBook based on email
            {
                for (int j = i + 1; j < addressBook->contactCount; j++)
                {
                    if (strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email) > 0)
                    {
                        Contact temp = addressBook->contacts[i];        //swap using temp variable
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;

        default:
            printf("\nInvalid sort criteria.\n");
            return;
    }
//print all contacts sorted as per user requirements
    printf("\n----- Contact List -----\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nName : %s\nPhone: %s\nEmail: %s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

    //If no. of contacts =0, populate using dummy contacts
    if(addressBook->contactCount == 0)
    populateAddressBook(addressBook);
    
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    //check if max contact count is reached
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress Book is full! Cannot add new contact.\n");
        return;
    }

    //create new Contact named newcontact
    Contact newContact;
    //getchar();

    printf("\nEnter Name  : ");                             //get new contact name from user
    fgets(newContact.name, sizeof(newContact.name), stdin); 
    newContact.name[strcspn(newContact.name, "\n")] = '\0'; //remove trailing newline

    printf("Enter Phone : ");                               //get new contact phone from user
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0'; //remove trailing newline

    printf("Enter Email : ");                                 //get new contact phone from user
    fgets(newContact.email, sizeof(newContact.email), stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0'; // remove trailing newline

    // --- Duplicate check ---
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        //Check if new contact entered is already present in file
        if (strcmp(addressBook->contacts[i].name, newContact.name) == 0 ||
            strcmp(addressBook->contacts[i].phone, newContact.phone) == 0 ||
            strcmp(addressBook->contacts[i].email, newContact.email) == 0)
        {
            printf("\nA contact with the same name, phone, or email already exists!\n");
            return;
        }
    }

    addressBook->contacts[addressBook->contactCount++] = newContact;    //append newcontacts and count to AddressBook
    printf("\nContact added successfully!\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    if (addressBook->contactCount == 0)         //check if no contacts are present
    {
        printf("\nNo contacts to search.\n");
        return;
    }

    char keyword[50];   //'keyword' variable to read user input
    int found = 0;      //flag variable named 'flag'

    //Read user input whether name/phone/email
    printf("\nEnter name/phone/email to search: ");
    scanf(" %[^\n]", keyword);

    //iterate through all entries
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, keyword) ||
            strstr(addressBook->contacts[i].phone, keyword) ||
            strstr(addressBook->contacts[i].email, keyword))    //search for entered keyword in name/email/phone
        {
            printf("\nContact Found:\nName : %s\nPhone: %s\nEmail: %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);         //if found print the contact 
            found = 1;                                      //raise flag
        }
    }

    if (!found)                                             //flag!=0 return no matching contact found
        printf("\nNo matching contact found.\n");
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    if (addressBook->contactCount == 0)                     //Check if contacts are saved to be edited
    {
        printf("\nNo contacts available to edit.\n");
        return;
    }

    char name[50]; //variable to store the input
    //getchar();   // clear leftover newline
    
    printf("\nEnter the name of the contact to edit: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';                       //To clear the trailing new line

    // Find the contact
    int index = -1;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name))   // partial match allowed
        {
            index = i;                                     // store the index
            break;
        }
    }

    if (index == -1)                                        //if no index match, return no contact found
    {
        printf("\nNo contact found with that name.\n");
        return;
    }

    Contact *c = &addressBook->contacts[index];            //New structure pointer pointing to address of the contact to be edited

    int choice;
    printf("\nEditing Contact: %s\n", c->name);            //Display contact to be edited

    printf("\nWhat do you want to edit?\n");               //read user ip on what fields to edit
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Edit all fields\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);                                   //store user input
    getchar(); // clear leftover newline

    char buffer[50];    //new variable 'buffer' to store new name/phone/email id to be entered

    switch (choice)
    {
        case 1: // Edit name
            printf("Enter new Name: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(c->name, buffer);                //copy buffer value into name field
            break;

        case 2: // Edit phone
            printf("Enter new Phone: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(c->phone, buffer);               //copy buffer value into phone field
            break;

        case 3: // Edit email
            printf("Enter new Email: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(c->email, buffer);               //copy buffer value into email id field
            break;

        case 4: // Edit all
            printf("Enter new Name: ");
            fgets(c->name, sizeof(c->name), stdin);
            c->name[strcspn(c->name, "\n")] = '\0';

            printf("Enter new Phone: ");
            fgets(c->phone, sizeof(c->phone), stdin);
            c->phone[strcspn(c->phone, "\n")] = '\0';

            printf("Enter new Email: ");
            fgets(c->email, sizeof(c->email), stdin);
            c->email[strcspn(c->email, "\n")] = '\0';
            break;

        default:
            printf("\nInvalid choice.\n");
            return;
    }

    printf("\nContact updated successfully!\n");
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete.\n");
        return;
    }

    char name[50];
    //getchar();   // clear leftover newline
    
    printf("\nEnter the name of the contact to delete: ");      //Read user input to find the contact to delete
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int index = -1;

    // find contact using strstr (partial match allowed)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name))   // partial match
        {
            index = i;                                     //store index value
            break;
        }
    }

    if (index == -1)
    {
        printf("\nNo contact found matching that name.\n");
        return;
    }

    // Show found contact and ask for confirmation
    char confirm;
    printf("\nContact found: %s (Phone: %s, Email: %s)\n",
           addressBook->contacts[index].name,
           addressBook->contacts[index].phone,
           addressBook->contacts[index].email);

    printf("Are you sure you want to delete '%s'? (y/n): ",
           addressBook->contacts[index].name);
    scanf(" %c", &confirm);                                     // ask user for confirmation

    while (getchar() != '\n');                                  //flush new line from previous input

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("\nDelete cancelled.\n");
        return;
    }

    // Shift contacts to fill the gap
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;
    printf("\nContact deleted successfully!\n");

}
