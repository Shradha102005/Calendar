#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDayOfWeek(int day, int month, int year);
void printMonthCalendar(int month, int year);
void printYearCalendar(int year);
void addNote();
void printNotes();
void addNoteToFile(int day, int month, int year, const char *note);
int countNotes();

int isLeapYear(int year);
int getDaysInMonth(int month, int year);

#define MAX_NOTES 100
#define MAX_NOTE_LENGTH 100
FILE *fp = NULL;

int main() 
{
    int choice;

    while (1) {
        printf("\nCalendar Application\n");
        printf("1. Find Out the Day\n");
        printf("2. Print all the days of the month\n");
        printf("3. Print calendar for a year\n");
        printf("4. Add Note\n");
        printf("5. Print Notes\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
            {
                int day, month, year;
                printf("Enter date (dd mm yyyy): ");
                scanf("%d %d %d", &day, &month, &year);
                int weekday = getDayOfWeek(day, month, year);
                switch (weekday) {
                    case 0: printf("The day is: Sunday\n"); 
                            break;
                    case 1: printf("The day is: Monday\n"); 
                            break;
                    case 2: printf("The day is: Tuesday\n"); 
                            break;
                    case 3: printf("The day is: Wednesday\n"); 
                            break;
                    case 4: printf("The day is: Thursday\n"); 
                            break;
                    case 5: printf("The day is: Friday\n"); 
                            break;
                    case 6: printf("The day is: Saturday\n"); 
                            break;
                }
                break;
            }
            case 2: 
            {
                int month, year;
                printf("Enter month and year (mm yyyy): ");
                scanf("%d %d", &month, &year);
                printMonthCalendar(month, year);
                break;
            }
            case 3:
            {
                int year;
                printf("Enter year: ");
                scanf("%d", &year);
                printYearCalendar(year);
                break;
            }
            case 4:
                addNote();
                break;
            case 5:
                printNotes();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

int getDayOfWeek(int day, int month, int year) 
{
    if (month < 3) 
    {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int f = day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J;
    return (f + 6) % 7;
}

void printMonthCalendar(int month, int year) 
{
    int daysInMonth = getDaysInMonth(month, year);
    int dayOfWeek = getDayOfWeek(1, month, year);

    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    for (int i = 0; i < dayOfWeek; i++) 
    {
        printf("    ");
    }
    for (int day = 1; day <= daysInMonth; day++) 
    {
        printf("%3d ", day);
        if ((day + dayOfWeek) % 7 == 0) 
        {
            printf("\n");
        }
    }
    printf("\n");
}

void printYearCalendar(int year) 
{
    for (int month = 1; month <= 12; month++) 
    {
        printf("\n%s %d\n", "Month", month);
        printMonthCalendar(month, year);
    }
}

void addNote() 
{
    if (countNotes() >= MAX_NOTES) 
    {
        printf("Note storage is full!\n");
        return;
    }

    int day, month, year;
    char note[MAX_NOTE_LENGTH];

    printf("Enter date for the note (dd mm yyyy): ");
    scanf("%d %d %d", &day, &month, &year);

    printf("Enter note: ");
    scanf("\n%[^\n\t]s", note);

    fp = fopen("notes.txt", "a");
    fprintf(fp, "%d %d %d %s\n", day, month, year, note);
    fclose(fp);
    printf("Note added successfully!\n");
}

void printNotes() 
{
    fp = fopen("notes.txt", "r");
    if (fp == NULL) 
    {
        printf("No notes available.\n");
        return;
    }
    
    int day, month, year;
    char note[MAX_NOTE_LENGTH];
    
    printf("Printing all notes:\n");
    while (fscanf(fp, "%d %d %d %[^\n]", &day, &month, &year, note) == 4) 
    {
        printf("Date: %02d/%02d/%04d\n", day, month, year);
        printf("Note: %s\n\n", note);
    }
    
    fclose(fp);
}

int countNotes() 
{
    fp = fopen("notes.txt", "r");
    if (fp == NULL) 
    {
        return 0;
    }

    int count = 0;
    int day, month, year;
    char note[MAX_NOTE_LENGTH];
    
    while (fscanf(fp, "%d %d %d %[^\n]", &day, &month, &year, note) == 4) 
    {
        count++;
    }
    
    fclose(fp);
    return count;
}

int isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) 
{
    switch (month) 
    {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 31;
    }
}