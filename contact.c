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
int searchContact(AddressBook *addressBook) 
{
	int count=0;
	/* Define the logic for search */
	int choice;
	int flag = 0;
	char str[50];
	printf("1.enter the name:\n2.enter the phone:\n3.enter the email:\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("enter the name:");
			scanf("%s",str);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				count = 0; 
				for(int j=0;str[j]!='\0';j++)
				{
					if(str[j] == addressBook->contacts[i].name[j])
					{
						count++;
					}

				}
				if(strlen(str)==count)
				{
					flag = 1;
					printf("%d\t%-20s %-20s %-20s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}

			}
			if(flag == 0)
			{
				printf("no contact found\n");
				return 1;
			}
			break;
		case 2:
			printf("enter the phone:");
			scanf("%s",str);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				count = 0; 
				for(int j=0;str[j]!='\0';j++)
				{
					if(str[j] == addressBook->contacts[i].phone[j])
					{
						count++;
					}

				}
				if(strlen(str)==count)
				{
					flag = 1;
					printf("%d\t %-20s %-20s %-20s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}

			}
			if(flag == 0)
			{
				printf("no contact found\n");
				return 1;
			}
			break;
		case 3:
			printf("enter the mail:");
			scanf("%s",str);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				count = 0; 
				for(int j=0;str[j]!='\0';j++)
				{
					if(str[j] == addressBook->contacts[i].email[j])
					{
						count++;
					}

				}
				if(strlen(str)==count)
				{
					flag = 1;
					printf("%d\t%-20s %-20s %-20s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}

			}
			if(flag == 0)
			{
				printf("no contact found\n");
				return 1;
			}
			break;
		default:
			printf("you have not entered the correct choice\n");
			break;
	}

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int serial_no;
	printf("enter the serial number:");
	scanf("%d",&serial_no);
	serial_no = serial_no-1;
	int choice,i;
	printf("1.edit the name:\n2.edit the phone number:\n3.edit the email:\n");
	scanf("%d",&choice);
	char str[100];
	switch(choice)
	{
		case 1:
			printf("enter the name:");
			scanf(" %[^\n]",str);
			for(i=0;str[i]!='\0';i++)
			{
				addressBook->contacts[serial_no].name[i] = str[i];
			}
			addressBook->contacts[serial_no].name[i] = '\0';
			break;
		case 2:
			printf("enter the phone number:");
			scanf("%s",str);
			for(i=0;i<str[i]!='\0';i++)
			{
				addressBook->contacts[serial_no].phone[i] = str[i];
			}
			addressBook->contacts[serial_no].phone[i] = '\0';
			break;
		case 3:
			printf("enter the email:");
			scanf("%s",str);
			for(i=0;i<str[i]!='\0';i++)
			{
				addressBook->contacts[serial_no].email[i] = str[i];
			}
			addressBook->contacts[serial_no].email[i] = '\0';
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
