#include "system.h"


int checkMobileFormat(char mobile[15])
{
    if (strlen(mobile) != 11)
        return 1;

    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(mobile[i]))
            return 1;
    }
    return 0;
}
int checkNameFormat(char check[40])
{
    int i=0;
    while(check[i]!='\0')
    {
        if(!((check[i]>='a'&&check[i]<='z')||(check[i]>='A'&&check[i]<='Z'|| check[i]==' ')))return 1;
            i++;
    }
    return 0;
}

int checkIdFormat(char id[20])
{
    if (strlen(id) != 14)
        return 1;

    for (int i = 0; i < 14; i++)
    {
        if (!isdigit(id[i]))
            return 1;
    }
    return 0;
}

int checkEmailFormat(char email[50])
{
    int i = 0;
    int atCount = 0;
    int dotCount = 0;
    int atPosition = -1;

    while (email[i] != '\0')
    {
        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }
        else if (email[i] == '.' && atPosition != -1)
        {
            dotCount++;
        }
        i++;
    }
    if (atCount == 1 && dotCount == 1 && atPosition > 0 && atPosition < i - 4)
    {
        return 1;
    }

    return 0;
}

int checkDate(char *reservationDate) {
    int resDay, resMonth, resYear;
    int curDay, curMonth, curYear;

    //dividing the string to numbers from the reservation date string
    sscanf(reservationDate, "%d-%d-%d", &resDay, &resMonth, &resYear);
     Color(8);
    printf("Enter the current date in format DD-MM-YYYY: ");
    scanf("%s", currentDate);

    if (sscanf(currentDate, "%d-%d-%d", &curDay, &curMonth, &curYear) != 3||!checkDateformat(currentDate)  ) {
            Color(4);
        printf("Invalid current date format.\n");
        return 0;
    }

    // Compare dates
    if (resYear > curYear)
    {
        printf("Check-in is not allowed before the check-in date.\n");
        return 0;
    }
    if (resYear == curYear)
    {
        if (resMonth > curMonth)
        {
            printf("Check-in is not allowed before the check-in date.\n");
            return 0;
        }
        if (resMonth == curMonth && resDay > curDay)
        {
            printf("Check-in is not allowed before the check-in date.\n");
            return 0;
        }
    }

    return 1; // Valid
}



int checkDateformat(char*Datto)
{
    int k=strlen(Datto),counter=0;
    int day1=0,month1=0,year1=0;

    for(int i=0; i<k; i++)
    {
        if(Datto[i]=='-') counter++;
        if(Datto[i]<'0'||Datto[i]>'9')
        {
            if(Datto[i]=='-')continue;
            return 0;
        }

    }
    if(counter!=2) return 0;
    sscanf(Datto,"%d-%d-%d",&day1,&month1,&year1);
    if(day1<1||day1>31||month1<1||month1>12||year1<1) return 0;
    return 1;


}


int compareDates(date d1, date d2)
 {
    if (d1.year != d2.year)
        return d1.year - d2.year;
    if (d1.month != d2.month)
        return d1.month - d2.month;
    if (d1.day != d2.day)
        return d1.day - d2.day;
    return 0; // Equal dates
}



void capitalizeAndFormatName(char name[40])
{
    int  i= 0, j = 0;
    int to_capital = 1;
    char formattedName[40];

    while (name[i] != '\0')
    {
        if (!isspace(name[i]))
        {
            if (to_capital)
            {
                formattedName[j] = toupper(name[i]);
                to_capital = 0;
                j++;
            }
            else
            {
                formattedName[j] = tolower(name[i]);
                j++;
            }
        }
        else if (j > 0 && !isspace(formattedName[j - 1]))
        {
            formattedName[j] = ' ';
            to_capital = 1;
            j++;
        }
        i++;
    }

    formattedName[j] = '\0';
    strcpy(name, formattedName);
}
