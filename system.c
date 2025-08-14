#include "system.h"


int RandomId()
{

    int min = 145500, max = 454555;  // Range of random numbers id

    srand(time(NULL));  // Seed the random number generator

    int num = (rand() % (max - min + 1)) + min;  // Generate random number

    return num;
}


void is_unique()
{
    loadReservations();
    int unique=RandomId();
    int i;
    for(i=0; i<numReservations; i++)
    {
        if(reservations[i].reservationID==unique)
            unique=RandomId();
    }
    reservations[i].reservationID=unique;

}


void removeLine(const char *filename, int lineToRemove)
{
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL)
    {
        printf("can not open file\n");//red
        return;
    }

    char reader[120];
    int line =1;
    while (fgets(reader, sizeof(reader), file))
    {
        if (line != lineToRemove)
        {
            fputs(reader, tempFile);
        }
        line++;
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(filename);
    rename("temp.txt", filename);
}


void sortDates()
{
    FILE *fptr;
    if ((fptr = fopen("reservations.txt", "r")) == NULL)
    {
        Color(4);
        printf("Failed to open reservations file\n");//red
        exit(1);
    }
    FILE *ftemp;
    if ((ftemp = fopen("Temp file.txt", "w")) == NULL)
    {
        Color(4);
        printf("Failed to open Temp file\n");//red
        fclose(fptr);  // Close the first file before exiting
        exit(1);
    }

    int i = 0;
    char reader[200];
    loadReservations();
    while (i < numReservations && fgets(reader, sizeof(reader), fptr))
    {
        char *token = strtok(reader, ",");
        reservations[i].reservationID = atoi(token);

        token = strtok(NULL, ",");
        reservations[i].roomNumber = atoi(token);

        token = strtok(NULL, ",");
        strcpy(reservations[i].status, token);

        token = strtok(NULL, ",");
        strcpy(reservations[i].customerName, token);

        token = strtok(NULL, ",");
        strcpy(reservations[i].nationalID, token);

        token = strtok(NULL, ",");
        reservations[i].nights = atoi(token);

        token = strtok(NULL, "-");
        reservations[i].check.day = atoi(token);

        token = strtok(NULL, "-");
        reservations[i].check.month = atoi(token);

        token = strtok(NULL, ",");
        reservations[i].check.year = atoi(token);

        token = strtok(NULL, ",");
        strcpy(reservations[i].email, token);

        token = strtok(NULL, "\n");
        strcpy(reservations[i].phone, token);

        i++;
    }
    numReservations = i;
    for (i = 0; i < numReservations - 1; i++)
    {
        for (int j = 0; j < numReservations - i - 1; j++)
        {
            if (compareDates(reservations[j].check, reservations[j + 1].check) > 0)
            {
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;
            }
        }
    }

    // Write sorted reservations to the temp file
    printf("sorted data\n");
    for (i = 0; i < numReservations; i++)
    {
        char checkDate[20];
        sprintf(checkDate, "%02d-%02d-%04d",
                reservations[i].check.day,
                reservations[i].check.month,
                reservations[i].check.year);
        fprintf(ftemp, "%d,%d,%s,%s,%s,%d,%s,%s,%s\n",
                reservations[i].reservationID,
                reservations[i].roomNumber,
                reservations[i].status,
                reservations[i].customerName,
                reservations[i].nationalID,
                reservations[i].nights,
                checkDate,
                reservations[i].email,
                reservations[i].phone);
                Color(11);
        printf("%d,%d,%s,%s,%s,%d,%s,%s,%s\n",
               reservations[i].reservationID,
               reservations[i].roomNumber,
               reservations[i].status,
               reservations[i].customerName,
               reservations[i].nationalID,
               reservations[i].nights,
               checkDate,
               reservations[i].email,
               reservations[i].phone);
    }
    fclose(fptr);
    fclose(ftemp);
    remove("reservations.txt");
    rename("Temp file.txt", "reservations.txt");
    Color(2);
    printf("Reservations sorted successfully.\n");//green
    promptMainMenuOrExit();

}



void promptMainMenuOrExit() {
    int choice;
    Color(8);
    printf("\n1. Back to Main Menu\n");
    printf("2. Exit the system\n");
    Color(6);
    printf("Choose an option: ");

    while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            Color(4);
            printf("Invalid input. Please enter (1-2):"); // Red
            while (getchar() != '\n'); // Clear buffer
        } else {
            if (choice == 1) {
                MainMenu();
            } else {
                Color(9);
                printf("\nGoodbye!!\n"); // Blue
                exit(0);
            }
        }
    }
}


// function to tell user to save or discard
int save()
{
    while(1)
    { int choice;
     Color(9);
    printf("\nWant To Save ?\n");
    printf("1.Save\n");
    printf("2.Discard Changes\n");
    Color(6);
    printf("Enter Choice: ");
    if (scanf("%d", &choice) != 1 || choice < 1|| choice > 2||(buffer=getchar())!='\n' )
        {
            // Handle invalid input (non-numeric)
            Color(4);
            printf("Invalid input. Please enter (1-2).\n");//red
            Color(7);
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch(choice)
        {
        case 1 :
            Color(2);
            printf("\nData are now Saved\n");
            Color(7);
            return 1;


        case 2 :
            Color(4);
            printf("Changes are Discarded\n");
            Color(7);
            return 0;
        }


    }

}

