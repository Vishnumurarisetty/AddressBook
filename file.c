/*
Name   : M.VISHNU
Project: AddressBook
Date   : 12th Aug 2024
 */
#include <stdio.h>
#include "file.h"

// Function to save contacts from AddressBook structure to a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
        // Open the file in write mode, creating it if it doesn't exist
        FILE *save = fopen("contact.csv","w+");
        if(save == NULL)
        {
                // Check if the file was successfully opened
                printf("File doesn't exist\n");
                return;
        }

        // Write the total count of contacts as the first line in the file
        fprintf(save,"#%d\n",addressBook->contactCount);

        // Iterate through each contact and write it to the file in CSV format
        for(int i=0;i<addressBook->contactCount;i++)
        {
                fprintf(save,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }

        // Close the file after writing
        fclose(save);
}

// Function to load contacts from a CSV file into the AddressBook structure
void loadContactsFromFile(AddressBook *addressBook) {
        int i;

        // Open the file in read mode
        FILE *load = fopen("contact.csv","r");

        // Read the total count of contacts from the first line of the file
        fscanf(load,"#%d\n",&addressBook->contactCount);

        // Iterate through the file to read each contact and store it in the AddressBook
        for(i=0;i<addressBook->contactCount;i++)
        {
                fscanf(load,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }

        // Update the contact count in the AddressBook structure
        addressBook->contactCount = i;

        // Close the file after reading
        fclose(load);
}
