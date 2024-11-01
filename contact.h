#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>
#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
    FILE *fptr_file ;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
int isvalidname(AddressBook *addressBook , char name[] ) ;
int isvalidphone(AddressBook *addressBook ,  char phone[] );
int isvalidmail(AddressBook *addressBook , char mail[]) ;
int findname( AddressBook *addressBook , const char *name);
int findphone(AddressBook *addressBook , const char *phone);
int findemail(AddressBook *addressBook , const char *email);
int openfile( AddressBook *addressBook);
#endif
