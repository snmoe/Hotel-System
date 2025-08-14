#include "system.h"


void checkIn()
{
    int reservationID;
    int found = 0;

    loadReservations();
    loadRooms(); // Read Both files
     Color(8);
    printf("Enter the Reservation ID: ");
    Color(7);
    while(scanf("%d", &reservationID)!=1 ||(buffer=getchar())!='\n' )
    {
        Color(4);
        printf("invalid input .please enter a number of reservation :");//red
        Color(7);
        while(getchar()!='\n')
            continue;
    }
    for (int i = 0; i < numReservations; i++)
    {
        if (reservationID == reservations[i].reservationID)
        {
            found = 1;

            // Check if the reservation is already checked in
            if (strcmp(reservations[i].status, "confirmed") == 0)
            {
                Color(4);
                printf("Check-in already completed for this reservation.\n");//red
                Color(7);
                promptMainMenuOrExit();

            }

            // Validate check-in date
            if(checkDateformat(reservations[i].checkInDate))
            {
                if (!checkDate(reservations[i].checkInDate))
                {

                promptMainMenuOrExit();
                }
            }

            if(save())
            {


            // Update reservation status
            strcpy(reservations[i].status, "confirmed");
            Color(2);
            printf("Check-in successful for Reservation ID: %d Room Number: %d\n", reservationID,reservations[i].roomNumber);//green
            Color(7);
            // Update room status to Reserved
            for (int j = 0; j < numRooms; j++)
            {
                if (rooms[j].roomNumber == reservations[i].roomNumber)
                {
                    strcpy(rooms[j].status, "Reserved");
                    break;
                }
            }

            // Save updated data
            saveReservations();
            saveRooms();
            promptMainMenuOrExit();
            }

        }
    }

    if (!found)
    {
        Color(4);
        printf("Reservation ID not found.\n");//red
        Color(7);

    } promptMainMenuOrExit();
}




void checkOut()
{
    int roomNumber;
    int found = 0,j;

    loadReservations(); // Load reservation data
    loadRooms();// Load room data
    Color(9);
    printf("Check-out");
    Color(7);
    while(1)
    {
        Color(8);
        printf("\nEnter the Room Number for Check-Out: ");
        Color(7);
        if (scanf("%d", &roomNumber) != 1 ||(buffer=getchar())!='\n')
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter a numeric number of the room.\n");//red
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Search for a reservation with the given room number
        for (int i = 0; i < numReservations; i++)
        {
            if (reservations[i].roomNumber == roomNumber && strcmp(reservations[i].status, "confirmed") == 0)
            {
                found = 1;


                // Update The Room Status
                for (j = 0; j < numRooms; j++)
                {
                    if (rooms[j].roomNumber == roomNumber)
                    {
                        strcpy(rooms[j].status, "Available");
                        break;
                    }
                }

                // Calculate and display the total bill
                int totalBill = reservations[i].nights * rooms[j].price;
                Color(8);
                printf("Customer Name: %s\n", reservations[i].customerName);
                printf("Room Number: %d\n", roomNumber);
                printf("Total Bill: %d$\n", totalBill);
                Color(7);

                if(save())
                {

                // Remove the reservation from the array and save to reservation file
                removeLine("reservations.txt",i+1);
                // Save updated data back to room file
                saveRooms();
                Color(2);
                printf("Check-out completed successfully for Room Number: %d\n", roomNumber);//green
                Color(7);
                }
            }
        }

        if (!found)
        {
            Color(4);
            printf("No confirmed reservation found for Room Number: %d\n", roomNumber);//red
            Color(7);

        }
                        promptMainMenuOrExit();

    }
}





