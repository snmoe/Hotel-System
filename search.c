#include "system.h"

void query()
{
    while(1)
    {


    loadReservations();
    loadRooms();
    int choice;
    Color(9);
    printf("Search By:\n");//blue
    Color(8);
    printf("1. Customer Name\n");
    printf("2. Room Number\n");
    printf("3. Room Status\n");
    Color(6);
    printf("Choose an option: ");
    if (scanf("%d", &choice) != 1|| choice<1 ||choice >3 || (buffer=getchar())!='\n' )
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter a numeric number (1-3).\n");//red
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

    switch (choice)
    {
    case 1:
    {
        // Search by Customer Name
        char Name[100];
        int found = 0;
        Color(8);
        printf("Enter Customer Name:");
        Color(7);
        fgets(Name, sizeof(Name), stdin);
        Name[strcspn(Name, "\n")] = '\0';
        for (int i = 0; i < numReservations; i++)
        {
            if (strcasecmp(Name, reservations[i].customerName) == 0)
            {
                found = 1;
                Color(9);
                printf("\nReservation Details:\n");//blue
                Color(8);
                printf("Reservation Id: %d\n", reservations[i].reservationID);
                printf("Room Number: %d\n", reservations[i].roomNumber);
                printf("Room Status: %s\n", reservations[i].status);
                printf("Check-in Date: %s\n", reservations[i].checkInDate);
                printf("Number of Nights: %d\n", reservations[i].nights);
                printf("Customer Name: %s\n", reservations[i].customerName);
                printf("National Id: %s\n", reservations[i].nationalID);
                printf("Phone Number: %s\n", reservations[i].phone);
                printf("Email: %s\n", reservations[i].email);
            }
        }
        if (!found)
        {
            Color(4);
            printf("Customer Name '%s' not found.\n", Name);//red
        }
        promptMainMenuOrExit();
    }

    case 2:
    {
        // Search by Room Number
        int roomNumber, found = 0;
        Color(9);
        printf("Enter Room Number:");
       if (scanf("%d", &roomNumber) != 1||roomNumber<1001 || roomNumber>3002 ||(buffer=getchar())!='\n')
            {
                // Handle invalid input (non-numeric)
                Color(4);
                printf("Invalid input. Please enter a room number (1001-3002)\n");//red
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }
        for (int i = 0; i < numRooms; i++)
        {

            if (roomNumber == rooms[i].roomNumber)
            {
                found = 1;
                Color(9);
                printf("\nRoom Details:\n");//blue
                Color(8);
                printf("Room Number: %d\n", rooms[i].roomNumber);
                printf("Room Status: %s\n", rooms[i].status);

                if (strcmp(rooms[i].status,"Reserved") == 0)
                {
                    for (int j = 0; j < numReservations; j++)
                    {
                        if (reservations[j].roomNumber == roomNumber)
                        {
                            Color(9);
                            printf("\nReservation Details:\n");//blue
                            Color(8);
                            printf("Reservation Id: %d\n", reservations[j].reservationID);
                            printf("Check-in Date: %s\n", reservations[j].checkInDate);
                            printf("Number of Nights: %d\n", reservations[j].nights);
                            printf("Customer Name: %s\n", reservations[j].customerName);
                            printf("National Id: %s\n", reservations[j].nationalID);
                            printf("Phone Number: %s\n", reservations[j].phone);
                            printf("Email: %s\n", reservations[j].email);
                            break;
                        }
                    }
                }

            }
        }
        if (!found)
        {
            Color(4);
            printf("Room Number %d not found.\n", roomNumber);//red
        }

    }promptMainMenuOrExit();
    case 3:
    {
        // Search by Room Status
        char status[20];
        int found = 0;
        Color(8);
        printf("Enter The Room Status (Available/Reserved): ");
        gets(status); // Read room status
        for (int i = 0; i < numRooms; i++)
        {
            if (strcasecmp(status, rooms[i].status) == 0)
            {
                found = 1;
                printf("Room Number %d is %s.\n", rooms[i].roomNumber, rooms[i].status);
            }
        }
        if (!found)
        {
            Color(4);
            printf("No rooms found with status: %s.\n", status);//red
        }

    }
      promptMainMenuOrExit();
    }
}
}

void reservationReport()
{
    loadReservations();
    int customerNum = 0;
    int found = 0;
    char check[20];
    Color(9);
    printf("Enter Date in format (DD-MM-YYYY) to get all Reservations: ");
    while (1)
    {
        scanf("%s", check);
        if (checkDateformat(check)) break;
        Color(4);
        printf("The entered date is invalid. Please try again:\n");
        Color(8);
        printf("Enter Check-in Date (DD-MM-YYYY): ");
    }
    getchar(); // clear the buffer

    for (int i = 0; i < numReservations; i++)
    {
        if (strcasecmp(reservations[i].status, "confirmed") == 0 &&
            strcmp(reservations[i].checkInDate, check) == 0)
        {
            found = 1;
            customerNum++;
            Color(6);
            printf("\nCustomer #%d\n", customerNum);
            Color(8);
            printf("Customer Name: %s\n", reservations[i].customerName);
            printf("Customer ID: %s\n", reservations[i].nationalID);
            printf("Customer Email: %s\n", reservations[i].email);
            printf("Customer Phone: %s\n", reservations[i].phone);
            Color(7);
        }
    }

    if (!found)
    {
        Color(4);
        printf("There are no customers with this check-in date.\n");
        Color(7);
    }
    printf("\n");
    promptMainMenuOrExit();
}




void TrackRoomAvailability()
{

    while(1)
    {
        loadRooms();  // Load room data before checking
        int roomNumber;
        int found=0;
        Color(8);
        printf("Enter the Number of Room: ");
        Color(7);
        if (scanf("%d", &roomNumber) != 1|| roomNumber<1001 || roomNumber >3002||(buffer=getchar())!='\n')
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter a numeric room number (1001-3002).\n");//red
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        else
        {
            for (int i = 0; i < numRooms; i++)
            {
                if (rooms[i].roomNumber == roomNumber)
                {
                    if (strcmp(rooms[i].status, "Available") == 0)
                    {
                        found=1;
                        Color(2);
                        printf("Room %d is available.\n", roomNumber);//green
                        Color(7);
                    }
                    else
                    {
                        found=1;
                        Color(4);
                        printf("Room %d is not available.\n", roomNumber);//red
                        Color(7);
                    }

                }
            }
            if (! found)
            {
                Color(4);
                printf("room number not found\n");//red
                Color(7);
            }
            printf("\n");
            promptMainMenuOrExit();
        }
    }

}


void viewCustomerDetails()
{


        int choice;
        int ReservationId;
        int RoomNumber;
        int found = 0;
 while(1)
    {
        Color(9);
        printf("\nViewing By:\n");//blue
        Color(8);
        printf("1. Reservation ID\n");
        printf("2. Room Number\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1||(buffer=getchar())!='\n'  )
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter a numeric number (1-2).\n");//red
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }



        switch (choice)
        {
        case 1:

            loadReservations();
            Color(9);
            printf("Enter Reservation ID: ");
            if (scanf("%d", &ReservationId) != 1||(buffer=getchar())!='\n')
            {
                // Handle invalid input (non-numeric)
                Color(4);
                printf("Invalid input. Please enter a numeric Reservation ID.\n");//red
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }

            for (int i = 0; i < numReservations; i++)
            {
                if (reservations[i].reservationID == ReservationId)
                {
                    Color(9);
                    printf("\nCustomer Details:\n");//blue
                    printf("Name: %s\n", reservations[i].customerName);
                    printf("National ID: %s\n", reservations[i].nationalID);
                    printf("Phone: %s\n", reservations[i].phone);
                    printf("Email: %s\n", reservations[i].email);
                    printf("Room Number: %d\n", reservations[i].roomNumber);
                    printf("Reservation Status: %s\n", reservations[i].status);
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                Color(4);
                printf("No reservation found with ID: %d\n", ReservationId);//red
                promptMainMenuOrExit();
            }
            printf("\n");
            promptMainMenuOrExit();

        case 2:
            loadReservations();
            Color(8);
            printf("Enter Room Number: ");
            if (scanf("%d", &RoomNumber) != 1|| RoomNumber<1001 || RoomNumber >3002||(buffer=getchar())!='\n')
            {
                // Handle invalid input (non-numeric)
                Color(4);
                printf("Invalid input. Please enter a numeric room number (1001-3002).\n");//red
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }
            for (int i = 0; i < numReservations; i++)
            {
                if (reservations[i].roomNumber == RoomNumber)
                {
                    Color(8);
                    printf("\nCustomer Details:\n");//blue
                    printf("Name: %s\n", reservations[i].customerName);
                    printf("National ID: %s\n", reservations[i].nationalID);
                    printf("Phone: %s\n", reservations[i].phone);
                    printf("Email: %s\n", reservations[i].email);
                    printf("Reservation ID: %d\n", reservations[i].reservationID);
                    printf("Reservation Status: %s\n", reservations[i].status);
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                Color(4);
                printf("No reservation found for Room Number: %d\n", RoomNumber);//red
                promptMainMenuOrExit();
            }

            printf("\n");
            promptMainMenuOrExit();


        }
    }
}
