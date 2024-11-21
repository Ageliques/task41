#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_WORK_LENGTH 50
#define MAX_POSITION_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 100

typedef struct Contact {
    char first_name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char work[MAX_WORK_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char social[MAX_SOCIAL_LENGTH];
    struct Contact* next;
    struct Contact* prev;
} Contact;

Contact* head = NULL;

Contact* create_contact(char first_name[], char surname[], char last_name[], char work[], char position[], char phone[], char email[], char social[]) 
{
    Contact* new_contact = (Contact*)malloc(sizeof(Contact));
    strcpy(new_contact->first_name, first_name);
    strcpy(new_contact->surname, surname);
    strcpy(new_contact->last_name, last_name);
    strcpy(new_contact->work, work);
    strcpy(new_contact->position, position);
    strcpy(new_contact->phone, phone);
    strcpy(new_contact->email, email);
    strcpy(new_contact->social, social);
    new_contact->next = NULL;
    new_contact->prev = NULL;
    return new_contact;
}

void add_contact() {
    char first_name[MAX_NAME_LENGTH], surname[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH];
    char work[MAX_WORK_LENGTH], position[MAX_POSITION_LENGTH], phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH], social[MAX_SOCIAL_LENGTH];

    printf("Enter name: ");
    scanf("%s", first_name);
    printf("Enter surname: ");
    scanf("%s", surname);
    
    printf("Enter last name (leave it blank if not needed): ");
    getchar();
    fgets(last_name, MAX_NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter your place of work (leave it blank if not needed): ");
    fgets(work, MAX_WORK_LENGTH, stdin);
    work[strcspn(work, "\n")] = 0;

    printf("Enter the position (leave it blank if not needed): ");
    fgets(position, MAX_POSITION_LENGTH, stdin);
    position[strcspn(position, "\n")] = 0;

    printf("Enter the phone number (leave it blank if not needed): ");
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;

    printf("Enter the email address (leave it blank if not needed): ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter the link to the social network (leave it blank if not needed): ");
    fgets(social, MAX_SOCIAL_LENGTH, stdin);
    social[strcspn(social, "\n")] = 0;

    Contact* new_contact = create_contact(first_name, surname, last_name, work, position, phone, email, social);

    // Вставка в упорядоченный список
    if (head == NULL || strcmp(new_contact->surname, head->surname) < 0) {
        new_contact->next = head;
        if (head != NULL) {
            head->prev = new_contact;
        }
        head = new_contact;
        return;
    }

    Contact* current = head;
    while (current->next != NULL && strcmp(current->next->surname, new_contact->surname) < 0) {
        current = current->next;
    }

    new_contact->next = current->next;
    new_contact->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = new_contact;
    }
    
    current->next = new_contact;
}

void edit_contact(char first_name[], char surname[]) {
    Contact* current = head;
    
    while (current != NULL) {
        if (strcmp(current->first_name, first_name) == 0 && strcmp(current->surname, surname) == 0) {
            printf("Editing contact: %s %s\n", current->first_name, current->surname);
            printf("Enter a new place of work (leave it empty to save): ");
            getchar();
            fgets(current->work, MAX_WORK_LENGTH, stdin);
            current->work[strcspn(current->work, "\n")] = 0;

            printf("Enter a new position (leave it empty to save): ");
            fgets(current->position, MAX_POSITION_LENGTH, stdin);
            current->position[strcspn(current->position, "\n")] = 0;

            printf("Enter a new phone number (leave it blank to save): ");
            fgets(current->phone, MAX_PHONE_LENGTH, stdin);
            current->phone[strcspn(current->phone, "\n")] = 0;

            printf("Enter a new email address (leave it blank to save): ");
            fgets(current->email, MAX_EMAIL_LENGTH, stdin);
            current->email[strcspn(current->email, "\n")] = 0;

            printf("Enter a new link to the social network (leave it blank to save): ");
            fgets(current->social, MAX_SOCIAL_LENGTH, stdin);
            current->social[strcspn(current->social, "\n")] = 0;

            printf("The contact has been updated.\n");
            return;
        }
        current = current->next;
    }
    
    printf("The contact was not found.\n");
}

void delete_contact(char first_name[], char surname[]) {
    Contact* current = head;
    
    while (current != NULL) {
        if (strcmp(current->first_name, first_name) == 0 && strcmp(current->surname, surname) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next; // Удаляем первый элемент
            }
            
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            printf("The contact has been deleted.\n");
            return;
        }
        current = current->next;
    }

    printf("The contact was not found.\n");
}

void list_contacts() {
    if (head == NULL) {
        printf("The phone book is empty.\n");
        return;
    }

    Contact* current = head;
    
    while (current != NULL) {
        printf("Name: %s\n", current->first_name);
        printf("Surname: %s\n", current->surname);
        printf("Last name: %s\n", current->last_name);
        printf("Work: %s\n", current->work);
        printf("Position: %s\n", current->position);
        printf("Phone: %s\n", current->phone);
        printf("Email: %s\n", current->email);
        printf("Social: %s\n", current->social);
        printf("-----------------------------\n");
        
        current = current->next;
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contact\n");
        printf("3. Delete Contact\n");
        printf("4. List Contacts\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2: {
                char first_name[MAX_NAME_LENGTH], surname[MAX_NAME_LENGTH];
                printf("Enter the first name of the contact to edit: ");
                scanf("%s", first_name);
                printf("Enter the surname of the contact to edit: ");
                scanf("%s", surname);
                edit_contact(first_name, surname);
                break;
            }
            case 3: {
                char first_name[MAX_NAME_LENGTH], surname[MAX_NAME_LENGTH];
                printf("Enter the first name of the contact to delete: ");
                scanf("%s", first_name);
                printf("Enter the surname of the contact to delete: ");
                scanf("%s", surname);
                delete_contact(first_name, surname);
                break;
            }
            case 4:
                list_contacts();
                break;
            case 5:
                exit(0);
            default:
                 printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

