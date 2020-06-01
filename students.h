#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct student_t {
    char id[17]; 
    char lastname[17]; 
    char firstname[17]; 
    char patronumic[16]; 
    char faculty[25]; 
    char speciality[45]; 
} student_t;

// база данных студентов
typedef struct students_database_t {
    student_t *students;
    int size;
} students_database_t;

student_t read_student(char *id);

int find_student(students_database_t database, char *id);
void add_student(students_database_t *database);
void remove_student(students_database_t *database);
void edit_student(students_database_t *database); 
void get_student(students_database_t database); 

void save_students_database(students_database_t database, const char *path); 
students_database_t load_students_database(const char *path);