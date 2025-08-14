#include "system.h"

// Function to load users from file
void loadUsers()
{

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening users.txt\n");//red
        exit(1);
    }


    while(fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2)
    {
        (numUsers)++;
    }  // fscanf return a value of how many successful reads done

    fclose(file);
}





// Function to load reservations from file
void loadReservations()
{
    FILE *file = fopen("reservations.txt", "r");
    if (!file)
    {Color(4);
        printf("Error opening reservations.txt\n");//red
        Color(7);
        return;
    }

    char reader[200]; // Buffer to hold each line
    numReservations = 0;

    while (fgets(reader, sizeof(reader), file))   // Read each line from the file
    {

        char *token = strtok(reader, ",");  // Read a comma-delimited file
        if (token != NULL)
            reservations[numReservations].reservationID = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
            reservations[numReservations].roomNumber = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(reservations[numReservations].status, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(reservations[numReservations].customerName, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(reservations[numReservations].nationalID, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            reservations[numReservations].nights = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(reservations[numReservations].checkInDate, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(reservations[numReservations].email, token);
        token = strtok(NULL, "\n");
        if (token != NULL)
            strcpy(reservations[numReservations].phone, token);

        numReservations++;
    }

    fclose(file);
}


// Function to rewrite the file again from the beginning
void saveReservations()
{
    FILE *file = fopen("reservations.txt", "w");
    if (!file)
    {Color(4);
        printf("Error writing to reservations.txt");//red
        Color(7);
        exit(1);
    }

    for (int i = 0; i < numReservations; i++)
    {

        fprintf(file, "%d,%d,%s,%s,%s,%d,%s,%s,%s\n",
                reservations[i].reservationID,
                reservations[i].roomNumber,
                reservations[i].status,
                reservations[i].customerName,
                reservations[i].nationalID,
                reservations[i].nights,
                reservations[i].checkInDate,
                reservations[i].email,
                reservations[i].phone);

    }

    fclose(file);
}



// Function to load rooms from file
void loadRooms()
{
    FILE *file = fopen("Room.txt", "r");
    if (!file)
    {
        Color(4);
        printf("Error opening Room.txt\n");//red
        Color(7);
        return;
    }

    numRooms = 0;
    while (fscanf(file, "%d%30s%30s%d", &rooms[numRooms].roomNumber, rooms[numRooms].status,
                  rooms[numRooms].category, &rooms[numRooms].price) == 4)
    {
        numRooms++;
    }

    fclose(file);
}



// Function to save rooms in the correct format to a file
void saveRooms()
{

    FILE *file = fopen("Room.txt", "w");
    if (!file)
    {Color(4);
        printf("Error writing to Room.txt\n");//red
        Color(7);
        exit(1);
    }

    for (int i = 0; i < numRooms; i++)
    {
        fprintf(file, "%d %s %s %d\n", rooms[i].roomNumber, rooms[i].status, rooms[i].category, rooms[i].price);
    }

    fclose(file);
}
