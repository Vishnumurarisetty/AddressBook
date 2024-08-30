/*
Name   : M.VISHNU
Project: AddressBook
Date   : 12th Aug 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


// List contacts based on the sorting criteria
void listContacts(AddressBook *addressBook, int sortCriteria) {
        int i;
        switch(sortCriteria) {
                case 1:
                        // List contacts sorted by name
                        for (i = 0; i < addressBook->contactCount; i++) {
                                printf("%d\t %s\n", i + 1, addressBook->contacts[i].name);
                        }
                        break;
                case 2:
                        // List contacts sorted by phone number
                        for (i = 0; i < addressBook->contactCount; i++) {
                                printf("%d\t %s\n", i + 1, addressBook->contacts[i].phone);
                        }
                        break;
                case 3:
                        // List contacts sorted by email
                        for (i = 0; i < addressBook->contactCount; i++) {
                                printf("%d\t %s\n", i + 1, addressBook->contacts[i].email);
                        }
                        break;
                case 4:
                        // List contacts with all details
                        printf("%s\t %-20s %-20s %-20s\n","SL.NO","NAME","PHONE","EMAIL\n");
                        for (i = 0; i < addressBook->contactCount; i++) {

                                printf("%d\t %-20s %-20s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        }
                        break;
        }
}

// Initialize the address book and populate it with contacts
void initialize(AddressBook *addressBook) {
        addressBook->contactCount = 0;
        populateAddressBook(addressBook);

        // Load contacts from file during initialization (if needed)
        // loadContactsFromFile(addressBook);
}

// Save contacts to file and exit the program
void saveAndExit(AddressBook *addressBook) {
        saveContactsToFile(addressBook); // Save contacts to file
        exit(EXIT_SUCCESS); // Exit the program
}

// Create a new contact and add it to the address book
int createContact(AddressBook *addressBook) {
        Contact s1;
        int i;
        int is_duplicate = 0;

        // Prompt user to enter the contact name
        printf("Enter the name:\n");
        scanf(" %[^\n]", s1.name);
        for (i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].name, s1.name) == 0) {
                        is_duplicate = 1;
                        break;
                }
        }
        if (is_duplicate) {
                printf("%s name already exists!!!\n", s1.name);
                return 1;
        }

        // Prompt user to enter the phone number
        printf("Enter the 10 digit phone number:\n");
        scanf("%s", s1.phone);
        if (strlen(s1.phone) != 10) {
                printf("You entered %zu digits. Enter a valid phone number\n", strlen(s1.phone));
                return 1;
        }
        for (i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, s1.phone) == 0) {
                        is_duplicate = 1;
                        break;
                }
        }
        if (is_duplicate) {
                printf("%s number already exists!!!\n", s1.phone);
                return 1;
        }

        // Validate the phone number (only digits)
        for (i = 0; i < 10; i++) {
                if (s1.phone[i] < '0' || s1.phone[i] > '9') {
                        printf("Invalid phone number. Please enter digits only.\n");
                        return 0;
                }
        }

        printf("Successfully entered phone number.\n");

        // Prompt user to enter the email
        printf("Enter the email:\n");
        scanf("%s", s1.email);

        // Validate the email format
        int flag = 0;
        if (strchr(s1.email, '@') == NULL || strstr(s1.email, ".com") == NULL) {
                flag = 1;
        }
        for (i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, s1.email) == 0) {
                        is_duplicate = 1;
                        break;
                }
        }
        if (is_duplicate) {
                printf("%s Email already exists!!!\n", s1.email);
                return 1;
        }

        if (flag == 1) {
                // Invalid email format
                printf("Enter a valid email address\n");
                printf("<example@email.com>\n");
                return 0;
        } else {
                printf("Successfully entered the email.\n");
        }

        addressBook->contacts[addressBook->contactCount++] = s1;
        return 0; // Indicate successful addition
}
// Function to search for a contact in the address book
int searchContact(AddressBook *addressBook)
{
        int count = 0;  // Variable to count matching characters
        int choice;     // Variable to store user choice for search criteria
        int flag = 0;   // Flag to indicate if a contact was found
        char str[50];   // String to store the search input

        // Prompt user for search criteria
        printf("1. Enter the name:\n2. Enter the phone:\n3. Enter the email:\n");
        scanf("%d", &choice);

        // Switch based on user choice
        switch(choice)
        {
                case 1:
                        printf("Enter the name: ");
                        scanf("%s", str);
                        // Loop through all contacts to find a match by name
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                                count = 0;
                                for (int j = 0; str[j] != '\0'; j++)
                                {
                                        if (str[j] == addressBook->contacts[i].name[j])
                                        {
                                                count++;
                                        }
                                }
                                if (strlen(str) == count)
                                {
                                        flag = 1;
                                        printf("%d\t%-20s %-20s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                }
                        }
                        if (flag == 0)
                        {
                                printf("No contact found\n");
                                return 1;
                        }
                        break;

                case 2:
                        printf("Enter the phone: ");
                        scanf("%s", str);
                        // Loop through all contacts to find a match by phone
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                                count = 0;
                                for (int j = 0; str[j] != '\0'; j++)
                                {
                                        if (str[j] == addressBook->contacts[i].phone[j])
                                        {
                                                count++;
                                        }
                                }
                                if (strlen(str) == count)
                                {
                                        flag = 1;
                                        printf("%d\t%-20s %-20s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                }
                        }
                        if (flag == 0)
                        {
                                printf("No contact found\n");
                                return 1;
                        }
                        break;

                case 3:
                        printf("Enter the email: ");
                        scanf("%s", str);
                        // Loop through all contacts to find a match by email
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                                count = 0;
                                for (int j = 0; str[j] != '\0'; j++)
                                {
                                        if (str[j] == addressBook->contacts[i].email[j])
                                        {
                                                count++;
                                        }
                                }
                                if (strlen(str) == count)
                                {
                                        flag = 1;
                                        printf("%d\t%-20s %-20s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                }
                        }
                        if (flag == 0)
                        {
                                printf("No contact found\n");
                                return 1;
                        }
                        break;

                default:
                        printf("You have not entered the correct choice\n");
                        break;
        }
        return 0;
}

// Function to edit an existing contact in the address book
void editContact(AddressBook *addressBook)
{
        int serial_no; // Variable to store the serial number of the contact to be edited
        printf("Enter the serial number: ");
        scanf("%d", &serial_no);
        serial_no = serial_no - 1; // Adjust for zero-based index

        int choice, i; // Variables for user choice and loop index
        char str[100]; // String to store the new contact detail

        // Prompt user for the detail to edit
        printf("1. Edit the name:\n2. Edit the phone number:\n3. Edit the email:\n");
        scanf("%d", &choice);

        switch(choice)
        {
                case 1:
                        printf("Enter the new name: ");
                        scanf(" %[^\n]", str);
                        // Update the name in the address book
                        for (i = 0; str[i] != '\0'; i++)
                        {
                                addressBook->contacts[serial_no].name[i] = str[i];
                        }
                        addressBook->contacts[serial_no].name[i] = '\0';
                        break;

                case 2:
                        printf("Enter the new phone number: ");
                        scanf("%s", str);
                        // Update the phone number in the address book
                        for (i = 0; str[i] != '\0'; i++)
                        {
                                addressBook->contacts[serial_no].phone[i] = str[i];
                        }
                        addressBook->contacts[serial_no].phone[i] = '\0';
                        break;

                case 3:
                        printf("Enter the new email: ");
                        scanf("%s", str);
                        // Update the email in the address book
                        for (i = 0; str[i] != '\0'; i++)
                        {
                                addressBook->contacts[serial_no].email[i] = str[i];
                        }
                        addressBook->contacts[serial_no].email[i] = '\0';
                        break;

                default:
                        printf("You have not entered the correct choice\n");
                        break;
        }
}

void deleteContact(AddressBook *addressBook)
{
        /* Define the logic for deletecontact */
        int i, serial_no;

        // Display all contacts with their serial numbers
        for (i = 0; i < addressBook->contactCount; i++)
        {
                printf("%d\t %-20s %-20s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
}
// Prompt the user to enter the serial number of the contact to delete
