#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    int rollNumber;
    char name[100];
    char branch[50];
    int dob;
    int semister;

} STUDENT_INFO_t;

int max_record = 10;

STUDENT_INFO_t students[10];

void display_menu(void);
int read_menu_code(void);
void decode_menu_code(int8_t menu_code);
void display_all_records(STUDENT_INFO_t *record, int8_t max_record);
int check_roll_number(int roll_number, STUDENT_INFO_t *record, int8_t max_record);
int add_new_record(STUDENT_INFO_t *record, int8_t max_record);
int delete_record(STUDENT_INFO_t *record, int8_t max_record);

int main(void)
{
    int8_t menu_code;
    int8_t app_continue = 1;

    printf("Student record management program\n");

    while (app_continue)
    {
        display_menu();

        menu_code = read_menu_code();

        if (menu_code)
        {
            decode_menu_code(menu_code);
        }
        else
        {
            app_continue = 0;
            printf("Exiting application\n");
        }
    }

    return 0;
}

void display_menu(void)
{
    printf("Display all records --->1\n");
    printf("Add new record      --->2\n");
    printf("Delete a record     --->3\n");
    printf("Exit application    --->0\n");
    printf("Enter your choose here:");
}

int read_menu_code(void)
{
    int8_t menu_code;

    while (1)
    {
        if (scanf("%hhi", &menu_code) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            fflush(stdin); // Clear the input buffer
        }
        else
        {
            return menu_code;
        }
    }
}
void decode_menu_code(int8_t menu_code)
{
    int8_t ret;

    switch (menu_code)
    {
    case 1:
        printf("Displaying all students record\n");
        display_all_records(students, max_record);
        break;
    case 2:
        printf("Add a new record\n");
        ret = add_new_record(students, max_record);
        !ret ? printf("Record add unsuccessful\n") : printf("Record added successfully\n");
        break;
    case 3:
        printf("Delete a record\n");
        ret = delete_record(students, max_record);
        ret ? printf("Record deleted successfully\n") : printf("Record not found\n");
        break;
    default:
        printf("Invalid input\n");
    }
}

void display_all_records(STUDENT_INFO_t *record, int8_t max_record)
{
    int i;
    int found = 0;

    printf("\nRoll No.\tName\t\tBranch\t\tDOB\t\tSemester\n");
    printf("------------------------------------------------------------------------\n");

    for (i = 0; i < max_record; i++)
    {
        if (record[i].rollNumber != 0)
        {
            printf("%-8d\t%-20s\t%-20s\t%-8d\t%-8d\n",
                   record[i].rollNumber, record[i].name, record[i].branch, record[i].dob, record[i].semister);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No records found.\n");
    }
}

int check_roll_number(int roll_number, STUDENT_INFO_t *record, int8_t max_record)
{
    for (int i = 0; i < max_record; i++)
    {
        if (record[i].rollNumber == roll_number)
        {
            return 1; // Roll number found
        }
    }
    return 0; // Roll number not found
}
int add_new_record(STUDENT_INFO_t *record, int8_t max_record)
{
    int i, roll_number;

    for (i = 0; i < max_record; i++)
    {
        if (record[i].rollNumber == 0)
        {
            break;
        }
    }

    if (i == max_record)
    {
        printf("No space available.\n");
        return 0;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &roll_number);

    if (check_roll_number(roll_number, record, max_record))
    {
        printf("Roll number already exists.\n");
        return 0;
    }

    record[i].rollNumber = roll_number;

    printf("Enter Name: ");
    scanf("%s", record[i].name);

    printf("Enter Branch: ");
    scanf("%s", record[i].branch);

    printf("Enter Date of Birth (YYYYMMDD): ");
    scanf("%d", &record[i].dob);

    printf("Enter Semester: ");
    scanf("%d", &record[i].semister);

    return 1;
}

int delete_record(STUDENT_INFO_t *record, int8_t max_record)
{
    int roll_number;
    int found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll_number);

    for (int i = 0; i < max_record; i++)
    {
        if (record[i].rollNumber == roll_number)
        {
            record[i].rollNumber = 0;
            strcpy(record[i].name, "");
            strcpy(record[i].branch, "");
            record[i].dob = 0;
            record[i].semister = 0;
            found = 1;
            break;
        }
    }

    return found;
}
