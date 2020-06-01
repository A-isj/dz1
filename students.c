#include "students.h"


student_t read_student(char *id) {
    student_t student;

  
    strcpy(student.id, id);

    printf("Введите фамилию: ");
    scanf("%[^\n]%*c", student.lastname);

    printf("Введите имя: ");
    scanf("%[^\n]%*c", student.firstname);

    printf("Введите отчество: ");
    scanf("%[^\n]%*c", student.patronumic); 

    printf("Введите название факультета: ");
    scanf("%[^\n]%*c", student.faculty);

    printf("Введите специальность: ");
    scanf("%[^\n]%*c", student.speciality);

    return student; 
}

/
void save_student(FILE *f, student_t student) {
    fprintf(f, "%s;", student.id);
    fprintf(f, "%s;", student.lastname);
    fprintf(f, "%s;", student.firstname);
    fprintf(f, "%s;", student.patronumic);
    fprintf(f, "%s;", student.faculty);
    fprintf(f, "%s", student.speciality);
}

int find_student(students_database_t database, char *id) {
    
    for (int i = 0; i < database.size; i++)
        if (!strcmp(id, database.students[i].id))
            return i;

    return -1;
}

void add_student(students_database_t *database) {
    char id[17];
    printf("Введите номер зачётки: ");
    scanf("%[^\n]%*c", id);

    while (find_student(*database, id) != -1) { 
        printf("Студент с такой зачёткой уже есть, повторите ввод: ");
        scanf("%[^\n]", id);
    }

    database->students = (student_t *) realloc(database->students, (database->size + 1) * sizeof(student_t));
    printf("Введите информацию о студенте\n");
    database->students[database->size++] = read_student(id);
}

void remove_student(students_database_t *database) {
    if (database->size == 0) { 
        printf("Ещё не было добавлено ни одного студента\n");
       return;
    }

    char id[16];
    printf("Введите номер зачётки: ");
    scanf("%[^\n]%*c", id);

    int index = find_student(*database, id);

   
    if (index == -1) {
        printf("Нет студента с таким номерор зачётки\n"); 
        return;
    }

  
    for (database->size--; index < database->size; index++)
        database->students[index] = database->students[index + 1];
}


void edit_student(students_database_t *database) {
    if (database->size == 0) {
        printf("Ещё не было добавлено ни одного студента\n");
        return;
    }

    char id[16];
    printf("Введите номер зачётки: ");
    scanf("%[^\n]%*c", id);

    int index = find_student(*database, id); 

    if (index == -1) {
        printf("Нет такого студента\n");
        return;
    }

    printf("Введите новую информацию об этом студенте:\n");
    database->students[index] = read_student(id);
}


void get_student(students_database_t database) {
    if (database.size == 0) {
        printf("Ещё не было добавлено ни одного студента\n");
        return;
    }

    char id[16];
    printf("Введите номер зачётки: ");
    scanf("%[^\n]%*c", id);

    int index = find_student(database, id);

    if (index == -1) {
        printf("Нет такого студента\n");
        return;
    }

    printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
    printf("|   Номер зачётки   |      Фамилия      |        Имя        |     Отчество     |         Факультет         |                 Специальность                 |\n");
    printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
    printf("| %17s ", database.students[index].id);
    printf("| %17s ", database.students[index].lastname);
    printf("| %17s ", database.students[index].firstname);
    printf("| %16s ", database.students[index].patronumic);
    printf("| %25s ", database.students[index].faculty);
    printf("| %45s ", database.students[index].speciality);
    printf("|\n");
    printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
}


void save_students_database(students_database_t database, const char *path) {
    FILE *f = fopen(path, "w"); 

    for (int i = 0; i < database.size; i++) {
        save_student(f, database.students[i]);

        if (i < database.size - 1)
            fprintf(f, "\n");
    }

    fclose(f);
}

students_database_t load_students_database(const char *path) {
    FILE *f = fopen(path, "r"); 
    students_database_t database;
    database.size = 0;

    if (!f) {
        database.students = NULL;
        return database;
    }

    database.students = (student_t *) malloc(sizeof(student_t));

    while (!feof(f)) {
        fscanf(f, "%[^;]%*c", database.students[database.size].id);
        fscanf(f, "%[^;]%*c", database.students[database.size].lastname);
        fscanf(f, "%[^;]%*c", database.students[database.size].firstname);
        fscanf(f, "%[^;]%*c", database.students[database.size].patronumic);
        fscanf(f, "%[^;]%*c", database.students[database.size].faculty);
        fscanf(f, "%[^\n]%*c", database.students[database.size].speciality);

        database.size++;
        database.students = (student_t *) realloc(database.students, (database.size + 1) * sizeof(student_t));
    }

    fclose(f); 

    return database;
}