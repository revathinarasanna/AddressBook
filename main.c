/*                                   Name : N.Revathi
                                     Description : project on AddressBook
                                     Date : 30-09-2024 
                                     Sample input : Address Book Menu :
                                                     1. Create contact
                                                     2. Search contact
                                                     3. Edit contact
                                                     4. Delete contact
                                                     5. List all contacts
                                                     6.Save and Exit 
                                                     Enter your choice : 1
                                     Sample output : Enter your name : revath90
                                                     please enter alphabets only
                                                     Enter your name : @rev
                                                     please enter alpabets only
                                                     Enter your name : revathi
                                                     Enter mobile number : 2938op
                                                     please enter numbers only
                                                     Enter email id : .coml@
                                                     Invalid input please enter valid email id only
                                                     Enter email id : @.com
                                                     Invalid input please enter valid email id only
                                                     Enter email id : @l.com
                                                     Invalid input : please enter valid email id only
                                                     Enter email id : revathi@kk.com
                                                     Contact added successfully  
*/                                                    

#include <stdio.h>
#include "contact.h"
int main()
{
	int choice;
	AddressBook addressBook;
	openfile(&addressBook);
	initialize(&addressBook); // Initialize the address book
	do {
label :
		printf("\nAddress Book Menu:\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6.Save and Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);                             //switch case for the choice
		getchar();        
		switch (choice) {
			case 1:
				createContact(&addressBook);
				break;
			case 2:
				searchContact(&addressBook);
				break;
			case 3:
				editContact(&addressBook);
				break;
			case 4:
				deleteContact(&addressBook);
				break;
			case 5:
				listContacts(&addressBook);
				break;
			case 6:
				printf("Saving and Exiting...\n");
                              //  loadContactsFromFile(&addressBook);
				saveContactsToFile(&addressBook);
				break;    
			default:
				printf("Invalid choice. Please try again.\n");        //print when the input is greater the 6.
				goto label ;
		}
	} while (choice != 6);   

	return 0;
}
