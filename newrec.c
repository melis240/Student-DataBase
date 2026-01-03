#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() {
    printf("\033[2J\033[H");
}

void wait_for_key() {
    printf("\nНатиснете Enter, за да продължите...");
    getchar(); 
    getchar(); 
}

struct student {
    char first_name[20];
    char last_name[20];
    int roll_no;
    char spec[50];
    float per;
};

void addstudent();
void studentrecord();
void searchstudent();
void delete_student();

int main() {
    int choice = 0;
    while(choice != 5) {
        clear_screen();
        printf("\t\t\t=====СИСТЕМА ЗА УПРАВЛЕНИЕ НА ДАННИ НА СТУДЕНТИ=====");
        printf("\n\n\n\t\t\t\t     1. Добавете студент\n");
        printf("\t\t\t\t     2. Всички данни \n");
        printf("\t\t\t\t     3. Намерете студент\n");
        printf("\t\t\t\t     4. Изтрийте студент\n");
        printf("\t\t\t\t     5. Изход\n");
        printf("\t\t\t\t    _____________________\n");
        printf("\t\t\t\t     Избор: ");

        if (scanf("%d", &choice) != 1) break;

        switch(choice) {
            case 1: addstudent(); break;
            case 2: studentrecord(); break;
            case 3: searchstudent(); break;
            case 4: delete_student(); break;
            case 5:
                clear_screen();
                printf("\n\t\t\t\tБлагодаря, че използвахте програмата.\n\n");
                exit(0);
            default:
                printf("\n\t\t\t\tМоля, въведете валиден номер.");
                wait_for_key();
        }
    }
    return 0;
}

void addstudent() {
    char another;
    FILE *fp;
    struct student info;
    do {
        clear_screen();
        printf("\t\t\t\t======= ДОБАВЕТЕ ДАННИ ЗА УЧЕНИК =======\n\n");
        fp = fopen("information.txt", "ab");

        printf("\t\t\tВъведете име              : "); scanf("%s", info.first_name);
        printf("\t\t\tВъведете фамилия          : "); scanf("%s", info.last_name);
        printf("\t\t\tВъведете факултетен номер : "); scanf("%d", &info.roll_no);
        printf("\t\t\tВъведете специалност      : "); scanf("%s", info.spec);
        printf("\t\t\tВъведете среден успех     : "); scanf("%f", &info.per);

        if(fp == NULL) {
            fprintf(stderr, "\t\t\tГрешка при отваряне на файл.\n");
        } else {
            fwrite(&info, sizeof(struct student), 1, fp);
            fclose(fp);
            printf("\n\t\t\tДанните бяха успешно добавени!\n");
        }

        printf("\t\t\tДобавете още ученици? (y/n): ");
        scanf(" %c", &another);
    } while(another == 'y' || another == 'Y');
}

void studentrecord() {
    FILE *fp;
    struct student info;
    clear_screen();
    fp = fopen("information.txt", "rb");

    printf("\t\t\t\t======= ДАННИ НА СТУДЕНТИ =======\n\n");
    if(fp == NULL) {
        printf("\t\t\t\tНе са намерени данни.\n");
    } else {
        while(fread(&info, sizeof(struct student), 1, fp)) {
            printf("\n\t\t\t\t Име: %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\t Факултетен номер: %d", info.roll_no);
            printf("\n\t\t\t\t Специалност: %s", info.spec);
            printf("\n\t\t\t\t Среден успех: %.2f",  info.per);
            printf("\n\t\t\t\t --------------------------------\n");
        }
        fclose(fp);
    }
    wait_for_key();
}

void searchstudent() {
    struct student info;
    FILE *fp;
    int roll_no, found = 0;
    clear_screen();
    fp = fopen("information.txt", "rb");

    printf("\t\t\t\t======= ТЪРСЕНЕ НА УЧЕНИК =======\n\n");
    printf("\t\t\tВъведете номера на студента: ");
    scanf("%d", &roll_no);

    while(fread(&info, sizeof(struct student), 1, fp)) {
        if(info.roll_no == roll_no) {
            found = 1;
            printf("\n\t\t\tДанни за: %s %s (Факулттетен номер: %d)", info.first_name, info.last_name, info.roll_no);
            printf("\n\t\t\tСреден успех: %.2f", info.per);
        }
    }
    if(!found) printf("\n\t\t\tНе са намерени данни.");
    fclose(fp);
    wait_for_key();
}

void delete_student() {
    struct student info;
    FILE *fp, *fp1;
    int roll_no, found = 0;
    clear_screen();

    fp = fopen("information.txt", "rb");
    fp1 = fopen("temp.txt", "wb");

    printf("\t\t\t\t======= ИЗТРИВАНЕ НА ДАННИ =======\n\n");
    printf("\t\t\tВъведете номера на студента: ");
    scanf("%d", &roll_no);

    if(fp != NULL) {
        while(fread(&info, sizeof(struct student), 1, fp)) {
            if(info.roll_no == roll_no) found = 1;
            else fwrite(&info, sizeof(struct student), 1, fp1);
        }
        fclose(fp);
        fclose(fp1);

        if(found) {
            remove("information.txt");
            rename("temp.txt", "information.txt");
            printf("\n\t\t\tДанните бяха изтрити.");
        } else {
            remove("temp.txt");
            printf("\n\t\t\tСтудентът не е намерен.");
        }
    }
    wait_for_key();
}
