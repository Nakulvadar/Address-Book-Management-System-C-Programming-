#include <stdio.h>
#include "file.h"
#include<string.h>
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr=fopen("contact.csv","w");
    if(fptr==NULL)
    {
        printf("Erorr.\n");
        return;
    }
    fprintf(fptr, "%d\n", addressBook->contactCount);
    fprintf(fptr,"Name,Phone,Email\n");
    for(int i=0;i < addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.csv", "r");
    if (fptr == NULL)
    {
        printf("No saved contacts found.\n");
        return;
    }

    fscanf(fptr, "%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);  
    }

    fclose(fptr);
    printf("Contacts loaded successfully.\n");
}

