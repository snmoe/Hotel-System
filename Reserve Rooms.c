#include "system.h"

void reserveRoom()
{
    loadRooms();
    loadReservations();
    char category[20];
    int found = 0;
    int roomAssigned = 0;
    Color(9);
    printf("\nReservation\n"); // Blue
    Color(8);
    printf("Enter the Customer's name: ");
    scanf(" %[^\n]%*c",reservations[numReservations].customerName);
    capitalizeAndFormatName(reservations[numReservations].customerName);
    checkNameFormat(reservations[numReservations].customerName);

    while (checkNameFormat(reservations[numReservations].customerName))
    {
        Color(4);
        printf("Invalid Name, please try again.\n"); // Red
        Color(8);
        printf("Enter the Customer's name: ");
        scanf(" %[^\n]%*c",reservations[numReservations].customerName);
        capitalizeAndFormatName(reservations[numReservations].customerName);

    }
    Color(8);
    printf("Enter Customer's national ID: ");
    scanf(" %[^\n]%*c",reservations[numReservations].nationalID);
    int check = checkIdFormat(reservations[numReservations].nationalID);
    while (check)
    {
        Color(4);
        printf("Invalid national ID must be 14 numbers. Please try again.\n"); // Red
        Color(8);
        printf("Enter Customer's national ID: ");
        scanf(" %[^\n]%*c",reservations[numReservations].nationalID);
        check = checkIdFormat(reservations[numReservations].nationalID);
    }
    Color(8);
    printf("Enter Customer's email: ");
    scanf(" %[^\n]%*c",reservations[numReservations].email);
    check = checkEmailFormat(reservations[numReservations].email);
    while (!check)
    {
        Color(4);
        printf("Invalid Email. Please try again.\n"); // Red
        Color(8);
        printf("Enter Customer's email: ");
        scanf(" %[^\n]%*c", reservations[numReservations].email);
        check = checkEmailFormat(reservations[numReservations].email);
    }
    Color(8);
    printf("Enter Customer's Phone number: ");
    scanf(" %[^\n]%*c",reservations[numReservations].phone);
    check = checkMobileFormat(reservations[numReservations].phone);
    while (check)
    {
        Color(4);
        printf("Invalid phone number. Please try again.\n"); // Red
        Color(8);
        printf("Enter Customer's Phone number: ");
        scanf(" %[^\n]%*c", reservations[numReservations].phone);
        check = checkMobileFormat(reservations[numReservations].phone);
    }
    Color(8);
    printf("Enter Check-in Date (DD-MM-YYYY): ");
    while (1)
    {
        gets(reservations[numReservations].checkInDate);
        if (checkDateformat(reservations[numReservations].checkInDate)) break;
        Color(4);
        printf("The entered date is invalid. Please try again:\n"); // Red
        Color(8);
        printf("Enter Check-in Date (DD-MM-YYYY): ");
    }
    Color(8);
    printf("Enter the number of Nights: ");
    while(scanf("%d", &reservations[numReservations].nights)!=1||getchar() != '\n')
    {
        while (getchar() != '\n');
        Color(4);
        printf("invalid input!\n");
        Color(8);
        printf("Enter the number of Nights:");
    }
    Color(8);
    printf("Enter room category (SeaView, LakeView, or GardenView): ");
    gets(category);

    // Search for an available room in the given category
    while (!roomAssigned)
    {
        for (int i = 0; i < numRooms; i++)
        {
            if ((strcasecmp(rooms[i].status, "Available") == 0) && (strcasecmp(rooms[i].category, category) == 0))
            {
                // Assign room to reservation
                reservations[numReservations].roomNumber = rooms[i].roomNumber;
                roomAssigned = 1;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            Color(4);
            printf("No rooms available in this category. Enter another category:"); // Red
            gets(category);
        }
        else
        {
            break;
        }
    }

    // Generate unique reservation ID
    is_unique();

    // Update reservation status
    strcpy(reservations[numReservations].status, "unconfirmed");
    Color(2);
    printf("\nReservation Completed Successfully\n"); // Green
    printf("Your Reservation ID is: %d\n", reservations[numReservations].reservationID);
    printf("Room Number: %d\n", reservations[numReservations].roomNumber);

    // Increment reservation count
    numReservations++;

    // Save updated data to files
    saveReservations();
    saveRooms();
    promptMainMenuOrExit();
}



void editReservationDetails() {
    while(1)
    {
    int choice;
    int reservationID;
    int roomNumber;
    int found = 0;
    Color(9);
    printf("\nEditing By:\n");//blue
    Color(8);
    printf("1. Reservation ID\n");
    printf("2. Room Number\n");
    Color(6);
    printf("choose an option: ");
   if (scanf("%d", &choice) != 1 || choice < 1|| choice > 2||(buffer=getchar())!='\n' )
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter (1-2).\n");//red
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

    loadReservations(); // Load reservations once at the start

    switch (choice) {
        case 1:
            Color(8);
            printf("Enter Reservation ID: ");
    while(scanf("%d", &reservationID)!=1 ||(buffer=getchar())!='\n' )
    {
        Color(4);
        printf("invalid input .please enter a number of reservation :");//red
        while(getchar()!='\n')
            continue;
    }

            for (int i = 0; i < numReservations; i++) {
                if (reservations[i].reservationID == reservationID) {
                    found = 1;
                    Color(2);
                    printf("\nEditing Reservation for ID: %d\n", reservationID);
                    editReservationFields(i);
                    printf("Reservation updated successfully.\n");//green
                    return;
                }
            }
            if (!found) {
                    Color(2);
                printf("No reservation found with ID: %d\n", reservationID);//red
               promptMainMenuOrExit();
            }
            promptMainMenuOrExit();
            break;

        case 2:
            Color(8);
            printf("Enter Room Number: ");
             if (scanf("%d", &roomNumber) != 1|| roomNumber<1001 || roomNumber >3002||(buffer=getchar())!='\n')
            {
                // Handle invalid input (non-numeric)
                Color(4);
                printf("Invalid input. Please enter a numeric room number (1001-3002).\n");//red
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }

            for (int i = 0; i < numReservations; i++) {
                if (reservations[i].roomNumber == roomNumber) {
                    found = 1;
                    Color(2);
                    printf("\nEditing Reservation for Room Number: %d\n", roomNumber);
                    editReservationFields(i);
                    printf("Reservation updated successfully.\n");//green
                    return;
                }
            }
            if (!found) {
                    Color(4);
                printf("No reservation found for Room Number: %d\n", roomNumber);//red
                promptMainMenuOrExit();

            }
           promptMainMenuOrExit();

        default:
            Color(4);
            printf("Invalid choice. Please try again.\n");//red
    }
    }
}


void editReservationFields(int k) {
    char category[25];
    int found;
    while (1) {
        int choice;
        Color(9);
        printf("\nChoose a field to edit:\n");//blue
        Color(8);
        printf("1. Customer Name\n");
        printf("2. Phone Number\n");
        printf("3. Email\n");
        printf("4. Check-In Date\n");
        printf("5. Number of nights\n");
        printf("6. Category\n");
        printf("7. Exit options\n");
        Color(6);
        printf("Choose an option: ");
       if (scanf("%d", &choice) != 1 || choice < 1|| choice > 8||(buffer=getchar())!='\n' )
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter (1-7).\n");//red
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice)
        {
        case 1:
            Color(8);
            printf("Enter the Customer's name: ");
            gets(reservations[k].customerName);
            capitalizeAndFormatName(reservations[k].customerName);
            checkNameFormat(reservations[k].customerName);
            while (checkNameFormat(reservations[k].customerName))
            {
                Color(4);
                printf("Invalid Name, please try again.\n"); // Red
                Color(8);
                printf("Enter the Customer's name: ");
                gets(reservations[k].customerName);
            }
            Color(2);
            printf("continue to save the updates\n");
            break;

        case 2:
            Color(8);
            printf("Enter Customer's Phone number: ");
            scanf(" %[^\n]%*c",reservations[k].phone);
            int check = checkMobileFormat(reservations[k].phone);
            while (check)
            {
                Color(4);
                printf("Invalid phone number. Please try again.\n"); // Red
                Color(8);
                printf("Enter Customer's Phone number: ");
                scanf(" %[^\n]%*c", reservations[k].phone);
                check = checkMobileFormat(reservations[k].phone);
            }
            Color(2);
            printf("continue to save the updates\n");
            break;

        case 3:
            Color(8);
            printf("Enter Customer's email: ");
            scanf(" %[^\n]%*c",reservations[k].email);
            check = checkEmailFormat(reservations[k].email);
            while (!check)
            {
                Color(4);
                printf("Invalid Email. Please try again.\n"); // Red
                Color(8);
                printf("Enter Customer's email: ");
                scanf(" %[^\n]%*c", reservations[k].email);
                check = checkEmailFormat(reservations[k].email);
            }
            Color(2);
            printf("continue to save the updates\n");
            break;

        case 4:
            Color(8);
            printf("Enter Check-in Date (DD-MM-YYYY): ");
            while (1)
            {
                gets(reservations[k].checkInDate);
                if (checkDateformat(reservations[k].checkInDate)) break;
                Color(4);
                printf("The entered date is invalid. Please try again:\n"); // Red
                Color(8);
                printf("Enter Check-in Date (DD-MM-YYYY): ");
            }
            Color(2);
            printf("continue to save the updates\n");
            break;

        case 5:
            Color(8);
            printf("Enter the new number of Nights: ");
            while(scanf("%d", &reservations[k].nights)!=1||getchar() != '\n')
            {
                while (getchar() != '\n');
                Color(4);
                printf("invalid input!\n");
                Color(8);
                printf("Enter the new number of Nights: ");
            }
            Color(7);
            printf("continue to save the updates\n");
            break;

        case 6:

            loadRooms();

            while (1)
            {
                Color(8);
                printf("Enter a new room category: ");
                scanf(" %[^\n]%*c",category);

                found = 0;
                int oldRoomNumber = reservations[k].roomNumber;

                while(1)
                {
                    if((strcasecmp(category,"seaview")!=0) & (strcasecmp(category,"gardenview")!=0) & (strcasecmp(category,"lakeview")!=0))
                    {
                        Color(4);
                        printf("The required category is not available in our hotel,Enter another category (Seaview,Gardenview,Lakeview):");//red
                        scanf(" %[^\n]%*c",category);
                    }
                    else
                        break;
                }


                for(int u=0; u<numRooms; u++)
                {
                    if(rooms[u].roomNumber==oldRoomNumber)
                    {
                        while(1)
                        {
                            if(strcasecmp(category,rooms[u].category)==0)
                            {
                                Color(4);
                                printf("The required category matches the current one,Enter another category:");//red
                                scanf(" %[^\n]%*c",category);
                            }
                            else break;
                        }
                    }

                }

                for (int p = 0; p < numRooms; p++)
                {

                    if (strcasecmp(rooms[p].category, category) == 0 && strcasecmp(rooms[p].status, "available") == 0)
                    {
                        found = 1;

                        reservations[k].roomNumber = rooms[p].roomNumber;

                        strcpy(rooms[p].status, "Reserved");


                        for (int j = 0; j < numRooms; j++)
                        {
                            if (rooms[j].roomNumber == oldRoomNumber)
                            {
                                strcpy(rooms[j].status, "Available");
                                break;
                            }
                        }
                        Color(2);
                        printf("continue to save Room category to be %d.\n", rooms[p].roomNumber);//green
                        break;
                    }
                }

                if (found)
                {


                    break;
                }
                else
                {
                    Color(4);
                    printf("No available rooms in the %s category. Please enter another category.\n", category);//red
                }
            }

            break;
            while(1)
            {


            case 7:
                Color(8);
                printf("1.Exit without saving\n");
                printf("2.Exit and save the editing\n ");
                Color(6);
                printf("choose an option:");
                if (scanf("%d", &choice) != 1||(buffer=getchar())!='\n' || choice < 1|| choice > 2 )
                {
                    // Handle invalid input (non-numeric)
                    Color(4);
                    printf("Invalid input. Please enter a numeric number (1-2).\n");//red
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }

                if (choice==1)
                    promptMainMenuOrExit();
                else if (choice ==2)
                {  saveReservations();
                    if (found)
                    {


                        saveRooms();

                    }
                    return;
                }

            default:
                Color(4);
                printf("Invalid choice. Please try again.\n");//red
            }
        }
    }
}




void cancelReservation()
{
    loadRooms();
    loadReservations();
    int choice, found = 0, id, roomNum,j,i;
    while (1)
    {
        Color(9);
        printf("Cancel Reservation by:\n"); //blue
        Color(8);
        printf("1. Reservation ID\n");
        printf("2. Room Number\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1 ||(buffer=getchar())!='\n' )
        {
            Color(4);
            printf("Invalid input. Please enter 1 or 2.\n"); //red
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        else if (choice >=3)
        {
            Color(4);
            printf("Invalid input. Please enter (1-2).\n");//red
            continue;
        }

        if (choice == 1)
        {
            Color(8);
            printf("Enter Reservation ID: ");
            if (scanf("%d", &id) != 1)
            {
                Color(4);
                printf("Invalid input. Please enter a numeric ID.\n"); //red
                while (getchar() != '\n');
                continue;
            }

            // Search for reservation by ID
            for (int i = 0; i < numReservations; i++)
            {
                if (id == reservations[i].reservationID)
                {

                    found = 1;
                    if (strcmp("confirmed", reservations[i].status) == 0)
                    {
                        Color(4);
                        printf("Cannot cancel a confirmed reservation.\n"); //red
                        promptMainMenuOrExit();

                    }
                    else if (strcmp("unconfirmed", reservations[i].status) == 0)
                    {
                        if(save())
                        {
                            for(j=0; j<numRooms; j++)
                            {
                                if(rooms[j].roomNumber==reservations[i].roomNumber)
                                {
                                    break;
                                }
                            }
                            strcpy(rooms[j].status, "Available");
                            removeLine("reservations.txt", i + 1);
                            saveRooms();
                            Color(2);
                            printf("Successful reservation cancellation for Reservation ID %d.\n", id); //green
                            promptMainMenuOrExit();
                        }
                    }
                }
            }
            if (!found)
            {
                Color(4);
                printf("Reservation ID not found.\n"); //red

            }promptMainMenuOrExit();
        }
        else if (choice == 2)
        {
            Color(8);
            printf("Enter Room Number (1001-3002): ");
            if (scanf("%d", &roomNum) != 1 || roomNum < 1001 || roomNum > 3002)
            {
                Color(4);
                printf("Invalid input. Please enter a room number between 1001 and 3002\n"); // red
                while (getchar() != '\n');
                continue;
            }

            // Search for reservation by room number
            for (i = 0; i < numReservations; i++)
            {
                if (roomNum == reservations[i].roomNumber)
                {
                    found = 1;

                    if (strcmp("confirmed", reservations[i].status) == 0)
                    {
                        Color(4);
                        printf("Cannot cancel a confirmed reservation\n"); // red
                        promptMainMenuOrExit();
                    }
                    else if (strcmp("unconfirmed", reservations[i].status) == 0)
                    {
                        if (save())
                        {
                            // Find the corresponding room in the rooms array
                            for (j = 0; j < numRooms; j++)
                            {
                                if (rooms[j].roomNumber == roomNum)
                                {
                                    strcpy(rooms[j].status, "Available");
                                    break;
                                }
                            }

                            removeLine("reservations.txt", i + 1); // Remove reservation
                            saveRooms();                          // Save updated room statuses
                            Color(2);
                            printf("Successful reservation cancellation for Room Number %d\n", roomNum); // green
                            promptMainMenuOrExit();
                        }
                    }
                }
            }

            if (!found)
            {
                Color(4);
                printf("Room number not found.\n"); // red

            }promptMainMenuOrExit();
        }
    }
}




