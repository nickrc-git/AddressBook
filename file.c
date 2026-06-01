#include <stdio.h>
#include<string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.txt", "w");  //open file in write mode

    if (fp == NULL)
    {
        printf("\nError opening file for saving.\n");   //Error handling for file open failure 
        return;
    }

    //Write each contact into file
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s|%s|%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp); //file close
    printf("\nContacts saved successfully!\n"); //Send confirmation message
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.txt", "r");  //open file in read mode

    if (fp == NULL)
    {
        // No file yet; no error
        return;
    }

    char line[200];
    addressBook->contactCount = 0; // clear existing contacts

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        Contact newContact;

        // Remove newline
        line[strcspn(line, "\n")] = '\0';   //Remove trailing new line from fgets();

        // Split using '|'
        char *token = strtok(line, "|");
        if (token != NULL) strcpy(newContact.name, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(newContact.phone, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(newContact.email, token);

        // Add to AddressBook
        addressBook->contacts[addressBook->contactCount++] = newContact;
    }

    fclose(fp); //file close
    printf("\nContacts loaded successfully!\n");    //Send confirmation message
    
}