#include <stdio.h>
#include "file.h"
#include "contact.h"
void saveContactsToFile(AddressBook *addressBook)                                           //to save contacts to file 
{
    FILE *fptr_temp = fopen("temp.csv", "w");                                              //to check if the file is present or not
    if (fptr_temp == NULL)
    {
        perror("fopen");
        printf("Unable to open file \n");                                                        
        return;
    }
    fprintf(fptr_temp, "%d\n", addressBook->contactCount);                              //to print the count in the file
    for (int i = 0; i < addressBook->contactCount; i++) 
    {

       fprintf(fptr_temp, "%s", addressBook->contacts[i].name);                        //to print the name
       fprintf(fptr_temp, "%c",',' );                                                  // , as a separator
       fprintf(fptr_temp, "%s", addressBook->contacts[i].phone);                       //to print phone number
       fprintf(fptr_temp, "%c",',' );
       fprintf(fptr_temp, "%s", addressBook->contacts[i].email);                      //to print the email id
       fprintf(fptr_temp, "%c", '\n');
     
    }

    fclose(fptr_temp);
    printf("Contacts saved successfully to file.\n");                          
    remove("add.csv");                                                                  //to remove the file add.csv
    rename("temp.csv","add.csv");
}
int openfile( AddressBook *addressBook )
{
       addressBook -> fptr_file = fopen("add.csv","r");
       if( addressBook -> fptr_file == NULL)
       {
            perror("fopen");
            printf("file not found\n");
            return 0 ;
       }
       return 1 ;
}
void loadContactsFromFile(AddressBook *addressBook)                              //to load contacts from structure to file
{
      int i ;
      fscanf(addressBook->fptr_file, "%d\n", &addressBook->contactCount);              //to get the contact count from structure

      for( i = 0 ; i < addressBook -> contactCount ; i++ )
      {
            fscanf(addressBook->fptr_file , " %[^,]",addressBook -> contacts[i].name);    //to get name from structure
            fseek(addressBook->fptr_file,1,SEEK_CUR);
            fscanf(addressBook->fptr_file , " %[^,]",addressBook -> contacts[i].phone);   //to get phone number from structure 
            fseek(addressBook->fptr_file,1,SEEK_CUR);
            fscanf(addressBook->fptr_file , " %[^\n]",addressBook -> contacts[i].email);   //to get email id from structure
            fseek(addressBook->fptr_file,1,SEEK_CUR);
      }
      printf("Contact loaded successfully from file\n");
      //fclose(addressBook->fptr_file);
}
