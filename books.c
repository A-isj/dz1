#include "books.h"


book_t read_book(char *isbn) {
    book_t book;

    strcpy(book.isbn, isbn);

    printf("Введите авторов: ");
    scanf("%[^\n]%*c", book.authors);

    printf("Введите название книги: ");
    scanf("%[^\n]%*c", book.title);

    printf("Введите количество книг всего: ");
    scanf("%d%*c", &book.count);

    printf("Введите количество доступных книг: ");
    scanf("%d%*c", &book.available);

    return book; // }


void print_book(book_t book) {
    printf("| %16s ", book.isbn);
    printf("| %40s ", book.authors);
    printf("| %24s ", book.title);
    printf("| %10d ", book.count);
    printf("| %10d ", book.available);
    printf("|\n");
}


void save_book(FILE *f, book_t book) {
    fprintf(f, "%s;", book.isbn);
    fprintf(f, "%s;", book.authors);
    fprintf(f, "%s;", book.title);
    fprintf(f, "%d;", book.count);
    fprintf(f, "%d", book.available);
}


void print_books(books_database_t database) {
    if (database.size == 0) {
        printf("No book was added yet\n");
        return;
    }

    printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");
    printf("|       ISBN       |                  Авторы                  |         Название         | Количество |  Доступно  |\n");
    printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");

    for (int i = 0; i < database.size; i++)
        print_book(database.books[i]);

    printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");
}


int find_book(books_database_t database, char *isbn) {
    
    for (int i = 0; i < database.size; i++)
        if (!strcmp(isbn, database.books[i].isbn))
            return i;

    return -1;
}


void add_book(books_database_t *database) {
    char isbn[16];
    printf("Введите ISBN: ");
    scanf("%[^\n]%*c", isbn);

    while (find_book(*database, isbn) != -1) {
        printf("Книга с таким ISBN уже есть, введите другой ISBN: ");
        scanf("%[^\n]", isbn);
    }

    database->books = (book_t *) realloc(database->books, (database->size + 1) * sizeof(book_t));
    printf("Введите информацию о новой книге\n");
    database->books[database->size++] = read_book(isbn); //
}


void remove_book(books_database_t *database) {
    char isbn[16];
    printf("Введите ISBN: ");
    scanf("%[^\n]%*c", isbn);

    int index = find_book(*database, isbn);

  
    if (index == -1) {
        printf("Нет книги с таким номером\n");
       return;
    }

    
    for (database->size--; index < database->size; index++)
        database->books[index] = database->books[index + 1];
}


void edit_book(books_database_t *database) {
    char isbn[16];
    printf("Введите ISBN: ");
    scanf("%[^\n]%*c", isbn);

    int index = find_book(*database, isbn);


    if (index == -1) {
        printf("Нет книги с таким номером\n");
        return;
    }

    printf("Введите новые данные об этой книге\n");
    database->books[index] = read_book(isbn); 
}


void edit_book_count(books_database_t *database) {
    char isbn[16];
    printf("Введите ISBN: ");
    scanf("%[^\n]%*c", isbn);

    int index = find_book(*database, isbn);

    
    if (index == -1) {
        printf("Нет книги с таким номером\n");
       return;
    }

    printf("Введите новое количество книг: ");
    scanf("%d%*c", &database->books[index].count);

    if (database->books[index].count < database->books[index].available)
        database->books[index].available = database->books[index].count;
}


void save_books_database(books_database_t database, const char *path) {
    FILE *f = fopen(path, "w");

    for (int i = 0; i < database.size; i++) {
        save_book(f, database.books[i]);

        if (i < database.size - 1)
            fprintf(f, "\n");
    }

    fclose(f);
}


books_database_t load_books_database(const char *path) {
    FILE *f = fopen(path, "r");
    books_database_t database;

    if (!f) {
        database.size = 0;
        database.books = NULL;
        return database;
    }

    database.books = (book_t *) malloc(sizeof(book_t));
    database.size = 0;

    while (!feof(f)) {
        fscanf(f, "%[^;]%*c", database.books[database.size].isbn);
        fscanf(f, "%[^;]%*c", database.books[database.size].authors);
        fscanf(f, "%[^;]%*c", database.books[database.size].title);
        fscanf(f, "%d%*c", &database.books[database.size].count);
        fscanf(f, "%d%*c", &database.books[database.size].available);

        database.size++;
        database.books = (book_t *) realloc(database.books, (database.size + 1) * sizeof(book_t));
    }

    fclose(f); 
    return database;
}