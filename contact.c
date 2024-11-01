#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
int isvalidname(AddressBook *addressBook ,  char name[])                             //to check the name is alphabets or not
{
	int i ;
	for ( i = 0 ; i < strlen(name) ; i++ )
	{  
		if(!(name[i] >= 'A' && name[i] <= 'Z') &&
				!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] == '\t') &&!(name[i] == ' '))
		{
			return 0 ;                                   
		}
	}
	return 1 ;
}     


int isvalidphone(AddressBook *addressBook ,  char phone[])                          //to check the mobile number is numbers or not
{
	int i ;
	for ( i = 0 ; i < strlen(phone) ; i++ )
	{

		if(!(phone[i] >= '0' && phone[i] <= '9'))
		{                 
			return 0 ;
		}
	}
	if(strlen(phone) != 10 )
	{
		return 0 ;
	}
	for( i = 0 ; i < addressBook -> contactCount ; i++ )
	{
		if(strcmp( addressBook -> contacts[i].phone , phone) == 0)
		{
			return -1 ;
		}
	}
	return 1 ;
}
int isvalidemail(AddressBook *addressBook , char email[] ) 
{
	int i ;
	char *atsign = strchr( email , '@');                                                  //to check the email contains @ or not
	char *dotsign = strstr( email ,".com") ;                                              //to check the email contain .com or not           
	if( atsign == NULL || dotsign == NULL || dotsign < atsign)  
	{
		return 0 ;
	}
        if( atsign == email)
        {
               return 0 ;
        } 
       if( dotsign - atsign <= 1 )
	{
		return 0 ;
	}
	for ( char *ptr = atsign+1 ; ptr < dotsign ; ptr++ )
	{
		if(!(*ptr >= 'A' && *ptr <= 'Z') &&  !( *ptr >= 'a' && *ptr <= 'z') && !(*ptr >= '0' && *ptr <= '9'))
		{
			return 0 ;
		}
	}
	for( i = 0 ; i < addressBook -> contactCount ; i++ )                                   //to check for duplicate names
	{
		if(strcmp( addressBook -> contacts[i].email , email) == 0)
		{
			return -1 ;
		}
	}
	return 1 ;
}
int findname( AddressBook *addressBook , const char *name)                                    //to find the name present or not
{
	int i , count = 0 ;
	for ( i = 0 ; i  < addressBook ->contactCount ; i++ )                                                                                                       {   
		if(strcmp(addressBook->contacts[i].name,name)==0)                            //for comparing the names in the list
		{
			printf("\nContact found \n Name is %s \n Phone no is %s \n Email id is %s\n\n",                                                                         addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			count++;       
		}
	}
	return count ;
}	   
int findphone( AddressBook *addressBook , const char *phone)                                 //to find the mobile number 
{
	int i ;
	for ( i = 0 ; i  < addressBook->contactCount ; i++ )
	{
		if(strcmp(addressBook->contacts[i].phone , phone)==0)                       //comparing with the phone number is present or not
		{
			return i ;                                                          //to return the index
		}
	}
	return -1 ;
}

int findemail( AddressBook *addressBook , const char *email )                              //to find the email id
{
	int i ;
	for ( i = 0 ; i  < addressBook->contactCount ; i++ )
	{
		if(strcmp(addressBook->contacts[i].email , email)==0)                    //comparing the email id is present or not 
		{
			return i ;                                                       //return the index
		}
	}
	return -1 ;
}

void initialize(AddressBook *addressBook) {                                            
	addressBook->contactCount = 0;
	//populateAddressBook(addressBook);
	// Load contacts from file during initialization (After files)
	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook )                                                   //To create the contact
{
	if( addressBook -> contactCount >= MAX_CONTACTS)
	{
		printf("Address Book is full\n");
		return;
	}
	int namevalidation , phonevalidation , emailvalidation;
label :
	printf("\nEnter Name : ");                                                               //To create a name
	scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
	namevalidation =  isvalidname(addressBook , addressBook->contacts[addressBook->contactCount].name);  //for validation function call
	if(namevalidation == 0)
	{
		printf("Invalid input .Please enter alphabet characters only\n");
		goto label;
	}

label2:
	printf("Enter Mobile Number : ");                                                             //To create a mobile number
	scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
	phonevalidation = isvalidphone(addressBook , addressBook->contacts[addressBook->contactCount].phone);
	if(phonevalidation == 0)
	{ 
		printf("Invalid input .Please enter digits only\n");
		goto label2 ;
	}
	else if( phonevalidation == -1)                                                          //to check for the validation
	{
		printf("Duplicate phone number is found.Please enter other mobile number\n");
		goto label2 ;
	}

label3:
	printf("Enter Email Id : ");                                                             //To create email id
	scanf("%s",addressBook->contacts[addressBook->contactCount].email);
	emailvalidation = isvalidemail(addressBook , addressBook->contacts[addressBook->contactCount].email) ;
	if(emailvalidation == 0 )
	{
		printf("Invalid input.Please enter valid email id only\n");     
		goto label3 ;
	}
	else if(emailvalidation == -1)                                                //to check for the validation
	{
		printf("Duplicate email id is found .Please enter valid email id \n");
		goto label3 ;
	}
	addressBook -> contactCount++ ;                                             //to increase contact count
	printf("Contact added successfully\n");

}
void searchContact(AddressBook *addressBook)                                       //to search the contacts
{

	int search , i , found ;
	char searchname[50] , searchphone[50],searchemail[50] ;                   //array declaration
label :
	printf("\nChoose the choice\n");
        printf("1.Search by Name\n2.Search by Mobile Number\n3.Search by Email Id\n");       //choices 
	scanf("%d",&search);
	getchar();
	switch(search)
	{
		case 1 :
label1 :
			printf("Enter Name :");
			scanf("%[^\n]",searchname);
			getchar();
			if( isvalidname(addressBook , searchname) == 0)                       //to validate the name
			{
				printf("Invalid input .Please enter alphabets only\n\n");
				goto label1 ;
			}
			else
			{      
				found = findname( addressBook , searchname) ;                 //to find the search name

				if( found  == 0 )
				{
					printf("No contact found with the name  %s\n\n",searchname);    //to print if the contact is not found
                                        break ;
				}
			}
			break ;
		case 2 :
label2 :
			printf("Enter Mobile Number : ");
			scanf("%s",searchphone);
			getchar();
			if(isvalidphone(addressBook , searchphone) == 0 )                      //to validate the phone number
			{  
				printf("Invalid input or duplicate.Please enter digits only\n\n");   
				goto label2 ;
			}
			else
			{
				found = findphone( addressBook , searchphone);               //to find the search mobile number
				if(found != -1)
				{
					printf("Contact found \n Name is %s \n Phone no is %s \n Email id is %s\n\n",                                                                             addressBook->contacts[found].name,addressBook->contacts[found].phone,addressBook->contacts[found].email);

				}
				else
				{  
				          	printf("No contact found with the phone no %s\n\n",searchphone);   //to print if contact is not found 
                                                break ;
				}
			}
			break ;
		case 3 :
label3 :     
			printf("Enter Email Id :");
			scanf("%s",searchemail);
			getchar();
			if(isvalidemail(addressBook , searchemail)==0)                   //To validate the email
			{ 
				printf("Invalid input or duplicate found .Please enter valid email id only\n\n");  
				goto label3 ;
			}
			else
			{         
				found = findemail( addressBook , searchemail) ;            //To find the searchemail 
				if(found != -1)
				{
					printf("Contact found \n Name is %s \n Phone no is %s \n Email id is %s\n\n",                                                                             addressBook->contacts[found].name,addressBook->contacts[found].phone,addressBook->contacts[found].email);

				}
				else 
				{
					printf("No contact found with the email %s\n\n",searchemail);   //to print if the email is not present
                                         break ;
				}
			}
 
 			break ;
		default :
			printf("Invalid option please enter 1 or 2 or 3 \n\n");                      //to print if choice is not 1 or 2 or 3
			goto label ;
	}
}

void editContact(AddressBook *addressBook)                                                        //to edit the contact
{
	int  found  , search , foundindex = -1 , i ;
	char newname[200] , newphone[200] , newemail[200] , name[200] , phone[200] , email[200]  ;     
label3 :
	printf("\nChoose the choice\n");
        printf("1.Edit by Name\n2.Edit by Phone Number\n3.Edit by Email Id\n");                   //Choices 
	scanf("%d",&search);
	getchar();
	switch(search)
	{
		case 1 : 
label :
			printf("Enter Name  :");
			scanf(" %[^\n]",name);
			if( isvalidname(addressBook , name) )                                    //to validate the name
			{
				found = findname( addressBook ,name ) ;                          //to find the name is present or not 
				if( found > 1 )
				{       
                                        //if duplicate names find then it will check with the mobile number
					printf("\nSimilar contact names found,so please enter the phone Number :\n") ; 
					scanf("%s",phone);
					foundindex = -1 ;                                            
					for(i  = 0 ; i < addressBook -> contactCount ; i++)
					{
						if (strcmp(addressBook->contacts[i].name, name) == 0 &&          
						    strcmp(addressBook->contacts[i].phone, phone) == 0)  //comparing the mobile numbers
						{
							foundindex = i;                     
							break;
						}
					}
					if( foundindex == -1)
					{
						printf("contact not found \n\n");                      //to print if the contact is not found
						return ;
					}
				}
				else if( found == 1)                                           //if one contact is found then this will execute
				{
					for(i = 0 ; i < addressBook ->contactCount ; i++)
					{
						if( strcmp( addressBook->contacts[i].name,name)==0)    //comparing with names present in the list
						{
							foundindex = i ;
                                                        break ;
						}
					}
				}
                                else
                                {  
                                        printf("Contact not found\n");                      //print if contact is not found
                                        return ;
                                }
      
			}
			else
			{
				printf("Invalid name .Please enter valid name only\n\n");           //to print if invalid input is given
				goto label ;
			}
			break ;   
		case 2 :
label1 :
			printf("Enter Mobile Number  :");                                      
			scanf("%s",phone);
			if( isvalidphone(addressBook ,phone))                            //to validate the mobile number
			{
				found = findphone( addressBook ,phone );
				if( found == -1)
				{
					printf("Contact not found\n\n");
					break ;
				}
			}
			else
			{
				printf("Invalid mobile number .Please enter valid mobile number only\n\n");   //to print if the input is valid name
				goto label1 ;
			}
			break ;
		case 3 :
label2 :
			printf("Enter Email Id  :");
			scanf("%s",email);
			if( isvalidemail(addressBook ,email))                                         //to validate the email id
			{
				found = findemail( addressBook ,email );                              //to find if the email id is present or not
				if( found == -1)
				{
					printf("Contact not found\n\n");
					break ;
				}
			}
			else
			{
				printf("Invalid email id .Please enter valid email id only\n\n");
				goto label2 ;
			}
			break ;
		default : 
			printf("Invalid input .Please Enter 1 or 2 or 3 only\n\n");                 
			goto label3 ;
	}


	int editchoice ;
label8 :
	printf("Choose what you want to change\n");
        printf("1.Name\n2.Phone number\n3.Email Id\n");
	scanf("%d",&editchoice);
	getchar() ;
	switch(editchoice)
	{
		case 1 :
label5 :
			printf("Enter new name :");
			scanf("%[^\n]",newname);
			if( isvalidname(addressBook , newname) == 1)                                           //to validate the new name
			{
				strcpy( addressBook -> contacts[foundindex].name , newname);                   //to copy the old name with new name
				printf("Name updated successfully\n\n");
			}
			else
			{
				printf("Invalid name or duplicate name found.Please enter valid name only\n");   //Invalid input
				goto label5 ;
			}
			break ;
		case 2 :
label6 :
			printf("Enter new phone number :");
			scanf("%s",newphone);
			if( isvalidphone(addressBook , newphone) == 1 )                                      //Validate the new phone number
			{
				 if (foundindex != -1) 
                                 {
                                      strcpy(addressBook->contacts[foundindex].phone, newphone);           //to copy old phone number with new phone
                                 }
                                 else 
                                 {
                                       strcpy(addressBook->contacts[found].phone, newphone);               
                                 }
				printf("Phone number updated successfully\n\n");
			}
			else
			{
				printf("Invalid phone number or duplicate number found .Please enter valid number only\n");
				goto label6 ;
			}
			break ;
		case 3 :
label7 :
			printf("Enter new email id :");                                                    
			scanf("%s",newemail);
			if( isvalidemail(addressBook , newemail) ==1)                                      //to validate the email id
			{
		                 if (foundindex != -1) 
                                 {
                                         strcpy(addressBook->contacts[foundindex].email, newemail);      //to copy old mail id with new mail id
                                 }
                                 else 
                                 {
                                         strcpy(addressBook->contacts[found].email, newemail);
                                 }		
                                 printf("Email id updated successfully\n\n");                             
			}
			else
			{
				printf("Invalid email id  or duplicate email id is found.Please enter valid email id  only\n");
				goto label7 ;
			}
			break ;
		default :
			printf("Invalid input .Please enter 1 or 2 or 3 only\n");              //to print for invalid input 
			goto label8 ;

	}
}
void deleteContact(AddressBook *addressBook)                         //to delete the contact
{ 
	int index , foundindex  , i  , search;
	char searchname[50],searchphone[50],searchemail[50] ;
label4 :
	printf("\nChoose the choice\n");
        printf("1.Name\n2.Mobile\n3.Email id\n");
	scanf("%d",&search);
	getchar();
	switch(search)
	{
		case 1 :
label1 :
			printf("Enter Name :");
			scanf("%[^\n]",searchname);
			getchar();
			if( !isvalidname(addressBook , searchname))                   //to validate the name
			{
				printf("Invalid input .Please enter alphabets only\n"); 
				goto label1 ;
			}
			else
			{

				index = findname( addressBook , searchname) ;                   
				if(  index > 1 )                                    //if more than 1 conatct is found
				{ 
					printf("Similar contact names found,so please enter the phone Number :\n") ;
					scanf("%s",searchphone);
					foundindex = -1 ;
					for(i  = 0 ; i < addressBook -> contactCount ; i++)
					{
						if (strcmp(addressBook->contacts[i].name, searchname) == 0 &&
						   strcmp(addressBook->contacts[i].phone, searchphone) == 0) //comparing the given contact with other contacts .
						{
							foundindex = i;          
							break ;
						}
					}

					if( foundindex != -1)
					{
						for( int i  = foundindex ; i < addressBook ->contactCount -1 ; i++)
						{
							addressBook->contacts[i] = addressBook->contacts[i+1] ;
						}
						addressBook ->contactCount-- ;                            //to reduce the contactcount
						printf("Contact deleted successfully\n\n");
					} 
					else
					{   
						printf("No contact found with the name  %s\n",searchname);
					}
				}
				else if( index == 1)                                                  //if one contact is found
				{

					foundindex = -1;
					for (i = 0; i < addressBook->contactCount; i++) 
					{
						if (strcmp(addressBook->contacts[i].name, searchname) == 0) 
						{
							foundindex = i;
							break;  
						}
					}
					if (foundindex != -1) 
					{
						for (i = foundindex; i < addressBook->contactCount - 1; i++)
						{
							addressBook->contacts[i] = addressBook->contacts[i + 1];
						}
						addressBook->contactCount-- ;                          //to reduce the contact count
						printf("Contact deleted successfully.\n\n");
					} 
				}
                                else
                                {
                                          printf("No contact found\n");                                  //print if no contact find
                                }
			}
			break ;    
		case 2 :
label2 :
			printf("Enter Mobile number :");                                            //To delete with mobile number
			scanf("%s",searchphone);
			getchar();
			if( !isvalidphone(addressBook , searchphone))                              //to validate the mobile number
			{
				printf("Invalid input.Please enter digits only\n\n");
				goto label2 ;
			}
			else
			{
				index = findphone( addressBook , searchphone) ;
				if( index  != -1 )
				{
					for( i = index ; i < addressBook ->contactCount -1 ; i++)
					{
						addressBook->contacts[i] = addressBook->contacts[i+1] ;
					}
					addressBook ->contactCount-- ;                                    //to reduce the count
					printf("Contact deleted  successfully\n\n");
				}
				else
				{
					printf("No contact found with the mobile number  %s\n\n",searchphone);
				}
			}                    
			break ;

		case 3 :
label3 :
			printf("Enter Email Id :");
			scanf("%s",searchemail);
			getchar();
			if( !isvalidemail(addressBook , searchemail))                                           //to validate the mail id
			{
				printf("Invalid input.Please enter valid email id \n\n");
				goto label3 ;
			}
			else
			{
				index = findemail( addressBook , searchemail) ;                          
				if( index  != -1 )                           
				{
					for( i = index ; i < addressBook ->contactCount -1 ; i++)
					{
						addressBook->contacts[i] = addressBook->contacts[i+1] ;
					}
					addressBook ->contactCount-- ;                                //to reduce the count
					printf("Contact deleted successfully\n\n");                             
				}
				else
				{
					printf("No contact found with the email  %s\n\n",searchemail);
				}
			}
			break ;
		default : 
			printf("Invalid input .Please enter 1 or 2 or 3 only\n\n");
			goto label4 ;

	}
}
void listContacts(AddressBook *addressBook)                                 //to list the contacts
{
	int i ;
	printf("\nlist of contacts are\n\n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-5s %-30s %-20s %-30s\n\n", "No.", "Name", "Mobile Number", "Email Id");
	for( i = 0 ; i < addressBook -> contactCount ; i++)
	{
		printf("%-5d %-30s %-20s %-30s\n", i + 1,
		addressBook->contacts[i].name,
		addressBook->contacts[i].phone,
		addressBook->contacts[i].email);                                     //to print the details
		printf("\n");
	}
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
}






















