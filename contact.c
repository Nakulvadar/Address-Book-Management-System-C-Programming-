#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

// Check for valid name or not
int validName(char *name) 
{
    if(name[0] == '\0') return 0;
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||(name[i] >= 'a' && name[i] <= 'z') ||name[i] == ' '))
        return 0;
    }
    return 1; 
}

// Check for valid phone number or not
int validphone(AddressBook *addressBook,char *phone)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1){
        printf("This number allready exist: \n");
        return 0;
    }
    if(phone[0]== '\0') return 0;
    if(phone[0]== '0') return 0;
    int len=0;
    for(int i=0;phone[i] != '\0';i++)
    {
        if(phone[i] <'0' || phone[i] >'9'){
            return 0;
        }
        len++;
    }
    return (len==10);
}
// Check for valid email or not
int validemail(AddressBook *addressBook,char *email)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1){
        printf("This Email allready exist: \n");
        return 0;
    }
    if(email[0] == '\0') return 0;

    int dotpos=0,atpos=0,len=0,count=0;
    for(int i=0;email[i] != '\0';i++){
        len++;
        if(email[i]>= 'A' && email[i] <= 'Z' || email[i] == ' '){
            return 0;
        }

        if(email[i]=='@'){

            atpos=i;
            count++;
        }
        if(email[i] == '.'){
            dotpos=i;
        }
    }
    if (len >= 4 && strcmp(&email[len - 4], ".com") != 0) {
        return 0;
    }
    if(count!=1) return 0;
    if( atpos < 1) return 0;
    if(dotpos < atpos+2) return 0;
    if(len - dotpos < 3) return 0;
    return 1;
}
//Search Name
void searchName(AddressBook *addressBook,char *name)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(name,addressBook->contacts[i].name)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
        }
    }
    if(!found)
    {
        printf("Not found your name.");
    }
}
//Search Phone
void searchPhone(AddressBook *addressBook,char *phone)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(!found)
    {
        printf("Not found your Phone.");
    }
}
//Search Email
void searchEmail(AddressBook *addressBook,char *email)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(!found)
    {
        printf("Not found your Email.");
    }
}

void listContacts(AddressBook *addressBook)
{
if(addressBook->contactCount == 0)
{
    printf("Contacts Not Found\n");
    return;
}
// Sort contacts based on the chosen criteria
for(int i=0;i<addressBook->contactCount-1;i++)
{ 
    for(int j=0;j<addressBook->contactCount-1-i;j++)
    {
        if(strcmp(addressBook->contacts[j].name , addressBook->contacts[j+1].name)>0)
        {
            Contact temp=addressBook->contacts[j];
            addressBook->contacts[j]=addressBook->contacts[j+1];
            addressBook->contacts[j+1]=temp;
        }
    }
}


printf("\nContact list..\n");
for(int i=0;i<addressBook->contactCount;i++)
{
    printf("\nContact %d:\n",i+1);
    printf("Name  %s\n",addressBook->contacts[i].name);
    printf("phone %s\n",addressBook->contacts[i].phone);
    printf("Email %s\n\n",addressBook->contacts[i].email);
}
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    if(addressBook->contactCount>=MAX_CONTACTS){
        printf("\nThe address book is full. \n");
        return;
    }
    else
    {
        Contact new_contact;
        printf("\nEnter %d Contact \n",addressBook->contactCount+1);
        
        printf("Enter the contact name :");
        scanf(" %[^\n]",new_contact.name);
        int i=validName(new_contact.name); 
        if(i==0){
            printf("\nPlese enter valid name..\n");
            return;
        }
        
        printf("Enter the contact phone :");
        scanf(" %[^\n]",new_contact.phone);
        i=validphone(addressBook,new_contact.phone); 
        if(i==0){ 
            printf("\nPlese enter valid phone number..\n");
            return;
        }
        
        printf("Enter the contact email :");
        scanf(" %[^\n]",new_contact.email);
        i=validemail(addressBook,new_contact.email); 
        if(i==0){
            printf("\nPlese enter valid Email..\n");
            return;
        }
        addressBook->contacts[addressBook->contactCount]=new_contact;
        addressBook->contactCount++;
    }
    
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choice;
    char detail[200];
    do
    {
        printf("\nSearch Menu:\n");
        printf("1.Search By Name: \n");
        printf("2.Search By Phone: \n");
        printf("3.Search By Email: \n");
        printf("4.Exit Searching.\n");
        printf("\nEnter your choice: ");
        scanf(" %d",&choice);
        switch(choice)
        {
            case 1:
            printf("Enter your Name for search: ");
            scanf(" %[^\n]",detail);
            searchName(addressBook,detail);
            break;

            case 2:
            printf("Enter your Phone number for search: ");
            scanf(" %[^\n]",detail);
            searchPhone(addressBook,detail);
            break;

            case 3:        
            printf("Enter your Email for search: ");
            scanf(" %[^\n]",detail);
            searchEmail(addressBook,detail);
            break;

            case 4:
            printf("Exit\n");
            break;

            default:
            printf("Invalid input\n");
            break;
        }
    }while(choice != 4);
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    int choice,i=0;
    char detail[200];
    printf("Enter Name /Phone /Email of contact to want edit: ");
    scanf(" %[^\n]",detail);
    int found=-1,count=0;
    for(int i=0;i < addressBook->contactCount;i++){
        if(strcmp(detail,addressBook->contacts[i].name)==0 ||strcmp(detail,addressBook->contacts[i].phone)==0 ||strcmp(detail,addressBook->contacts[i].email)==0)
        {
            printf("Found At index: %d = %s |%s |%s\n",count,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=i;
            count++;
        }
    }
    if (count == 0) {
        printf("No matching contact found.\n");
        return;
    }
   if (count > 1) {
        char refine[200];
        printf("Multiple contacts found with same name.\n");
        printf("Enter phone number OR email to refine: ");
        scanf(" %[^\n]", refine);
        found=-1;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(refine, addressBook->contacts[i].phone) == 0 ||
                strcmp(refine, addressBook->contacts[i].email) == 0) 
            {
                found = i;
                break;
            }
        }
        if (found == -1) {
        printf("Contact not found\n");
        return;
        }
    }
    do
    {
        printf("\nMenu for Edit\n");
        printf("1.Edit Name: \n");
        printf("2.Edit Phone number: \n");
        printf("3.Edit Email: \n");
        printf("4.Exit Edit menu: \n");
        printf("Enter you choise: ");
        scanf("%d",&choice);
        char n_detail[200];
        switch(choice)
        {
            case 1:
            printf("Enter the new Name: ");
            scanf(" %[^\n]",n_detail);
            i=validName(n_detail); 
            if(i==0){ 
            printf("\nPlese enter valid name\n");
            }
            else{
                strcpy(addressBook->contacts[found].name,n_detail);
                printf("Name updated successfully\n");
                return;
            }
            break;

            case 2:
            printf("Enter the new phone number: ");
            scanf(" %[^\n]",n_detail);
            i=validphone(addressBook,n_detail); 
            if(i==0){ 
            printf("\nPlese enter valid phone number\n");
            }
             else{
                strcpy(addressBook->contacts[found].phone,n_detail);
                printf("Phone updated successfully\n");
                return;
            }
            break;

            case 3:
            printf("Enter the new Email: ");
            scanf(" %[^\n]",n_detail);
            i=validemail(addressBook,n_detail); 
            if(i==0){ 
            printf("\nPlese enter valid Email\n");
            }
             else{
                strcpy(addressBook->contacts[found].email,n_detail);
                printf("Email updated successfully\n");
                return;
            }
            break;

            case 4:
            printf("Exit Menu\n");
            break;

            default:
            printf("Invalid input\n");
            break;
        }

    }while(choice != 4);
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    int choice,i=0;
    char detail[200];
    printf("Enter Name /Phone /Email of contact to want delete: ");
    scanf(" %[^\n]",detail);
    int found=-1,count=0;
    for(int i=0;i < addressBook->contactCount;i++){
        if(strcmp(detail,addressBook->contacts[i].name)==0 ||strcmp(detail,addressBook->contacts[i].phone)==0 ||strcmp(detail,addressBook->contacts[i].email)==0)
        {
            printf("Found At index: %d = %s |%s |%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=i;
            count++;
        }
    }
    
    if (count == 0) {
        printf("No matching contact found.\n");
        return;
    }
     if (count > 1) {
        char refine[200];
        printf("Multiple contacts found with same name.\n");
        printf("Enter phone number OR email to refine: ");
        scanf(" %[^\n]", refine);

        found = -1;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(refine, addressBook->contacts[i].phone) == 0 ||strcmp(refine, addressBook->contacts[i].email) == 0) 
            {
                found = i;
                break;
            }
        }
        if (found == -1) {
        printf("Contact not found\n");
        return;
        }
    }
    do
    {
        printf("\nMenu for Delite\n");
        printf("1.Delete Contact: \n");
        printf("2.Exit delete menu: \n");
        printf("Enter you choise: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            for(int i=found;i < addressBook->contactCount-1;i++){
                addressBook->contacts[i]=addressBook->contacts[i+1];
            }
            addressBook->contactCount--;
            printf("Contact successfully deleted \n");
            return;

            case 2:
            printf("Exit Menu\n");
            break;

            default:
            printf("Invalid input\n");
            break;
        }

    }while(choice != 2);
}