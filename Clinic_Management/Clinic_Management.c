#include <stdio.h>
#include <stdlib.h>
#include"STD_Types.h"
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_SLOTS 5

typedef struct {
char name[50];
    int age;
    char gender;
    int id;
	} Patient;
typedef struct {
    int id;
    int slot;
} Reservation;


Patient patients[MAX_PATIENTS];
u32 num_patients = 0;

Reservation reservations[MAX_SLOTS];
u32 num_reservations = 0;

void admin_mode();
void user_mode();
void add_patient();
void edit_patient();
void view_slots();
void reserve_slot();
void cancel_reservation();
void view_patient();
void view_reservations();
void select_mode();

const int admin_password = 1234;

void main() {
    select_mode();
}
void select_mode(){
	int mode;

    printf("Welcome to the clinic management system!\n");
    printf("Please choose a mode:\n");
    printf("1. Admin mode\n");
    printf("2. User mode\n");
    scanf("%d", &mode);

    if (mode == 1) {
        admin_mode();
    } else if (mode == 2) {
        user_mode();
    } else {
        printf("Invalid choice, exiting...");
        return ;
    }
}
void admin_mode() {
    u32 password_tries = 0;
    u32 password;

    printf("Enter password: ");
    scanf("%u", &password);

    while (password != admin_password && password_tries < 2) {
        printf("Incorrect password. %d tries left.\n", 2 - password_tries);
        printf("Enter password: ");
        scanf("%u", &password);
        password_tries++;
    }

    if (password == admin_password) {
		 printf("Welcome to admin mode!\n");

		while (1) {
        u32 choice;

        printf("\nPlease choose an action:\n");
        printf("1. Add new patient record\n");
        printf("2. Edit patient record\n");
		printf("3. view_slots\n");
        printf("4. Reserve a slot with the doctor\n");
        printf("5. Cancel reservation\n");
        printf("6. Return to Main Menu\n");
		printf("7. Exit...\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                edit_patient();
                break;
			case 3:
			    view_slots();
			    break;
            case 4:
                reserve_slot();
                break;
            case 5:
                cancel_reservation();
                break;
            case 6:
                return(select_mode());
			case 7:
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    } else {
        printf("Too many incorrect password attempts. Exiting...\n");
    }    
}

void user_mode() {
    printf("Welcome to user mode!\n");

    while (1) {
        u32 choice;

        printf("\nPlease choose an action:\n");
        printf("1. View patient record\n");
        printf("2. View today's reservations\n");
        printf("3. Return to Main Menu\n");
		printf("4. Exit...\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_patient();
                break;
            case 2:
                view_reservations();
                break;
            case 3:
                return (select_mode());
				break;
			case 4:
                return ;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void add_patient() {
    if (num_patients == MAX_PATIENTS) {
        printf("\nCannot add more patients. Maximum capacity reached.\n");
        return;
    }

    Patient p;
    printf("\nEnter patient name: ");
    scanf("%s", p.name);
    printf("Enter patient age: ");
    scanf("%d", &p.age);
    printf("Enter patient gender (M/F): ");
    scanf(" %c", &p.gender);
    printf("Enter patient ID: ");
    scanf("%d", &p.id);

    for (int i = 0; i < num_patients; i++) {
        if (patients[i].id == p.id) {
            printf("\nPatient with ID %d already exists. Cannot add patient.\n", p.id);
            return;
        }
    }

    patients[num_patients++] = p;
    printf("\nPatient added successfully.\n");
}

void edit_patient() {
    int id;
    printf("\nEnter patient ID: ");
    scanf("%d", &id);

    // Find patient with ID
    int index = -1;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }

    printf("\nPatient found.\n");
    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %c\n", patients[index].gender);

    printf("\nEnter new patient name: ");
    scanf("%s", patients[index].name);
    printf("Enter new patient age: ");
    scanf("%d", &patients[index].age);
    printf("Enter new patient gender (M/F): ");
    scanf(" %c", &patients[index].gender);

    printf("\nPatient information updated successfully.\n");
}
	
	void view_slots() {
    printf("Available slots:\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reservations[i].id == 0) {
            printf("%d. ", i + 1);
            switch (i) {
                case 0:
                    printf("2pm to 2:30pm\n");
                    break;
                case 1:
                    printf("2:30pm to 3pm\n");
                    break;
                case 2:
                    printf("3pm to 3:30pm\n");
                    break;
                case 3:
                    printf("4pm to 4:30pm\n");
                    break;
                case 4:
                    printf("4:30pm to 5pm\n");
                    break;
            }
        }
    }
}

void reserve_slot() {
    int id, slot;
    printf("\nEnter patient ID: ");
    scanf("%d", &id);
	int index1 = -1;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].id == id) {
            index1 = i;
            break;
        }
    }
    if (index1 == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }	
    printf("Enter desired slot: ");
    scanf("%d", &slot);

    if (slot < 1 || slot > MAX_SLOTS) {
        printf("\nInvalid slot number.\n");
        return;
    }

    if (reservations[slot-1].id != 0) {
        printf("\nSlot already reserved.\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }

    reservations[slot-1].id = id;
    reservations[slot-1].slot = slot;

    printf("\nSlot reserved successfully.\n");
}

void cancel_reservation() {
    int id;
    printf("\nEnter patient ID: ");
    scanf("%d", &id);
	int index = -1;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }	

   
	
	 int index1 = -1;
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reservations[i].id == id) {
            index1 = i;
            break;
        }
    }

    if (index1 == -1) {
        printf("\nReservation not found.\n");
        return;
    }

    reservations[index1].id = 0;
    reservations[index1].slot = 0;

    printf("\nReservation cancelled successfully.\n");
	
	
 
}

void view_patient() {
    u8 id;
    printf("\nEnter patient ID: ");
    scanf("%d", &id);

    u8 index = -1;
    for (u8 i = 0; i < num_patients; i++) {
        if (patients[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }

    printf("\nPatient found.\n");
    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %c\n", patients[index].gender);
}

void view_reservations() {
    printf("\nToday's reservations:\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reservations[i].id != 0) {
            printf("Slot %d: Patient ID %d\n", i + 1, reservations[i].id);
        }
    }
}

