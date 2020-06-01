#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct book_t {
    char isbn[16];
    char authors[40];
    char title[25];
    int count;
    int available;
} book_t;

typedef struct books_database_t {
    book_t *books;
    int size;
} books_database_t;

book_t read_book(char *isbn); 
void print_book(book_t book); 
void save_book(FILE *f, book_t book);

void print_books(books_database_t database);
void print_book_by_isbn(book_t *books, int n);
    
int find_book(books_database_t database, char *isbn); 
void add_book(books_database_t *database); 
void remove_book(books_database_t *database);
void edit_book(books_database_t *database)
void edit_book_count(books_database_t *database);

void save_books_database(books_database_t, const char *path);
books_database_t load_books_database(const char *path);