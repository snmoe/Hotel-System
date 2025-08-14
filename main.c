#include "system.h"

// Global Variables
User users[100];
int numUsers = 0;
Reservation reservations[200];
int numReservations = 0;
Room rooms[100];
int numRooms=0;
char buffer;
char currentDate[15];


int main()
{
    loadUsers();
    LoginMenu();
    return 0;
}

void Color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int Login()
{
    char username[50];
    char password[50];
Color(8);
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    Color(7);
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void LoginMenu() {
    int choice;

    while (1) {
        Color(9);
        printf("Welcome to Hotel Management System\n"); // Blue color
        Color(8);
        printf("1. Login\n");
        printf("2. Exit\n");
        Color(6);
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1 || (getchar() != '\n')) {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter a numeric number (1-2)\n"); // Red color
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        } else {
            switch (choice) {
                case 1:
                    while (1) {
                        if (Login()) {
                            Color(2);
                            printf("\nLogin Success\n"); // Green color
                            Color(7);
                            MainMenu(); // Call MainMenu
                            return;
                        } else {
                            Color(4);
                            printf("Something wrong in username or password. Please try again.\n"); // Red color
                        Color(7);
                            continue;
                        }
                    }
                    break;
                case 2:
                    Color(9);
                    printf("\nGoodbye!\n"); // Blue color
                    Color(7);
                    exit(0);
                default: // Handle input > 2
                    Color(4);
                    printf("Invalid input. Please enter a numeric number (1-2).\n"); // Red color
                    Color(7);
            }
        }
    }
}

void MainMenu() {
    while (1) {
        int choice;

            Color(9);
        printf("\nMain Menu:\n"); // Blue color
        Color(8);
        printf("1. Reserve a Room\n");
        printf("2. Check-in\n");
        printf("3. Cancel Reservation\n");
        printf("4. Check-out\n");
        printf("5. Check Room Availability\n");
        printf("6. View Customer Details\n");
        printf("7. Edit Reservation Details\n");
        printf("8. Query (search)\n");
        printf("9. Reservation Report\n");
        printf("10. Print sorted reservations\n");
        printf("11. Exit\n");
        Color(6);
        printf("Choose an option (1-11): ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 11 || getchar() != '\n') {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter (1-11).\n"); // Red color
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                reserveRoom();
                break;
            case 2:
                checkIn();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                checkOut();
                break;
            case 5:
                TrackRoomAvailability();
                break;
            case 6:
                viewCustomerDetails();
                break;
            case 7:
                editReservationDetails();
                break;
            case 8:
                query();
                break;
            case 9:
                reservationReport();
                break;
            case 10:
                sortDates();
                break;
            case 11:
                Color(9);
                printf("\nGoodbye!!\n"); // Blue color
                Color(7);
                exit(0);
        }
    }
}
