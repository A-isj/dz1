#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "books.h"
#include "students.h"


void book_menu() {
    books_database_t database = load_books_database("books.csv");
    int item;

    do {
        printf("Выберите действие\n");
        printf("0. Вывести все книги\n");
        printf("1. Добавить книгу\n");
        printf("2. Удалить книгу по номеру ISBN\n");
        printf("3. Изменить книгу\n");
        printf("4. Изменить количество книг\n");
        printf("5. Выйти\n");
        printf(">");
        scanf("%d%*c", &item);

       
        while (item < 0 || item > 5) {
            printf("Некорректный пункт меню, повторите ввод: ");
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
        printf("Выберите действие\n");
        printf("1. Добавить студента\n");
        printf("2. Удалить по номеру зачётки\n");
        printf("3. Редактировать по номеру зачётки\n");
        printf("4. Просмотреть по номеру зачётки\n");
        printf("5. Выйти\n");
        printf(">");
        scanf("%d%*c", &item);

       
        while (item < 1 || item > 5) {
            printf("Некорректный пункт меню, повторите ввод: ");
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
    printf("Выберите режим работы (книги, студенты): ");
    scanf("%[^\n]", mode);

    while (strcmp(mode, "книги") && strcmp(mode, "студенты")) {
        printf("Вы выбрали некорректный режим, повторите ввод: ");
        scanf("%[^\n]", mode);
    }

    if (!strcmp(mode, "книги")) {
        book_menu();
    }
    else {
        students_menu();
    }
    
    return 0;
}