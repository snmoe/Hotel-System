#ifndef system_h
#define system_h

// Needed  Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

// Structure to represent a user
typedef struct
{
    char username[50];
    char password[50];
} User;

// Structure to represent a date
typedef struct
{
    int day;
    int month;
    int year;
} date;

// Structure to represent a room
typedef struct
{
    int roomNumber;
    char status[30];
    char category[30];
    int price;
} Room;

// Structure to represent a reservation
typedef struct
{
    int reservationID;
    int roomNumber;
    char status[20];
    char customerName[50];
    char nationalID[20];
    int nights;
    char checkInDate[15];
    char email[50];
    char phone[15];
    date check;
} Reservation;

// Prototypes
int Login();
void LoginMenu();
void MainMenu();
void loadUsers();
void loadRooms();
void loadReservations();
void saveRooms();
void saveReservations();
void reserveRoom();
void checkIn();
void cancelReservation();
void checkOut();
void TrackRoomAvailability();
void viewCustomerDetails();
void editReservationDetails();
void query();
void reservationReport();
int  checkDate(char *reservationDate);
void removeLine(const char *filename, int lineToRemove);
int checkEmailFormat(char email[50]);
int checkIdFormat(char id[20]);
int checkMobileFormat(char mobile[15]);
int checkDateformat(char*Datto);
void sortDates();
int compareDates(date d1, date d2);
int checkNameFormat(char check[40]);
void promptMainMenuOrExit();
void is_unique();
void Color(int color);
int save();
void capitalizeAndFormatName(char name[40]);

// Global Variables
extern User users[100];
extern int numUsers;
extern Reservation reservations[200];
extern int numReservations;
extern Room rooms[100];
extern int numRooms;
extern char buffer;
extern char currentDate[15];


#endif // system.h
