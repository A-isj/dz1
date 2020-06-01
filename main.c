#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "books.h"
#include "students.h"


void book_menu() {
    books_database_t database = load_books_database("books.csv");
    int item;

    do {
        printf("�������� ��������\n");
        printf("0. ������� ��� �����\n");
        printf("1. �������� �����\n");
        printf("2. ������� ����� �� ������ ISBN\n");
        printf("3. �������� �����\n");
        printf("4. �������� ���������� ����\n");
        printf("5. �����\n");
        printf(">");
        scanf("%d%*c", &item);

       
        while (item < 0 || item > 5) {
            printf("������������ ����� ����, ��������� ����: ");
            scanf("%d%*c", &item);
        }

        switch (item) {
            case 0:
                print_books(database); 
                break;

            case 1:
                add_book(&database); 
                break;

            case 2:
                remove_book(&database); 
                break;

            case 3:
                edit_book(&database);
                break;

            case 4:
            edit_book_count(&database); 
                break;
        }

        printf("\n");
    } while (item != 5);

    save_books_database(database, "books.csv"); 
    free(database.books);
}

void students_menu() {
    students_database_t database = load_students_database("students.csv"); 
    int item; 

    do {
        printf("�������� ��������\n");
        printf("1. �������� ��������\n");
        printf("2. ������� �� ������ �������\n");
        printf("3. ������������� �� ������ �������\n");
        printf("4. ����������� �� ������ �������\n");
        printf("5. �����\n");
        printf(">");
        scanf("%d%*c", &item);

       
        while (item < 1 || item > 5) {
            printf("������������ ����� ����, ��������� ����: ");
            scanf("%d%*c", &item); 
        }

        switch (item) {
            case 1:
                add_student(&database);
                break;

            case 2:
                remove_student(&database);
                break;

            case 3:
                edit_student(&database); 
                break;

            case 4:
                get_student(database);
                break;
        }

        printf("\n");
    } while (item != 5);

    save_students_database(database, "students.csv");
    free(database.students);
}

int main() {
    setlocale(LC_ALL, "russian");
    system("chcp 1251");

    char mode[100]; 
    printf("�������� ����� ������ (�����, ��������): ");
    scanf("%[^\n]", mode);

    while (strcmp(mode, "�����") && strcmp(mode, "��������")) {
        printf("�� ������� ������������ �����, ��������� ����: ");
        scanf("%[^\n]", mode);
    }

    if (!strcmp(mode, "�����")) {
        book_menu();
    }
    else {
        students_menu();
    }
    
    return 0;
}