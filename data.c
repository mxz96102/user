#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 50

typedef struct user S_user;
typedef struct list S_list;
/*ver 1.0.0*/

/*the unit to make user information*/
struct user {
    unsigned id;
    char nickname[255];
};

/*the tabel with a posion to user unit, to able information store*/
struct list {
    unsigned rows;
    unsigned cols;
    S_user *value;
    unsigned id;
    S_list *right, *down;
    S_list *next;
};

S_list *head, *nowlist;
unsigned idnow = 0;

void create_list();

/*creat the structure of a null table */
void create_list() {
    unsigned rows = 0, cols = 0;
    S_list *temp, *p1, *p2;
    int n;

    /*to create the 0 row */

    for (n = 0; n < 11; n++) {
        temp = (S_list *) malloc(sizeof(S_list));
        if (temp == NULL) {
            printf("memory error\n");
            exit(1);
        }
        if (cols == 0) {
            head = temp;
        }
        if (cols != 0)
            p1->right = temp;
        temp->cols = cols;
        temp->rows = rows;
        cols++;
        p1 = temp;
        temp->down = temp;
    }

    cols = 0;
    rows = 1;

    p1 = head;
    for (n = 1; n <= MAX_ROW; n++) {
        temp = (S_list *) malloc(sizeof(S_list));
        if (temp == NULL) {
            printf("memory error\n");
            exit(1);
        }

        p1->down = temp;
        temp->cols = cols;
        temp->rows = rows;
        rows++;
        p1 = temp;
        temp->right = temp;
    }
    printf("list create completely!\n");
}

void create_user(unsigned id, char name[]) {
    S_list *temp = NULL, *p1, *p2, *p3;
    S_user *unit = NULL;
    unsigned rows = 1, col;



    /*get space for two **/
    unit = (S_user *) malloc(sizeof(S_user));
    temp = (S_list *) malloc(sizeof(S_list));

    if (unit == NULL || temp == NULL) {
        printf("memory error,0-m\n");
        exit(1);
    }

    if (nowlist != NULL)
        temp->next = nowlist;

    nowlist = temp;

    strcpy(unit->nickname, name);

    temp->id = id;
    unit->id = id;
    temp->value = unit;

    while (id > 10) {
        id -= 10;
        rows++;
    }
    col = id;

    temp->cols = col;
    temp->rows = rows;

    p1 = head;
    p3 = head;
    while (p1->rows != temp->rows)
        p1 = p1->down;
    p2 = p1;
    while (p1->right != p2) {
        p3 = p3->right;
        p1 = p1->right;
    }

    /*now p1 is left p3 is up p2 is row head*/
    p1->right = temp;
    temp->down = p3->down;
    p3->down = temp;
    temp->right = p2;
    idnow++;
    printf("user create completely , id : %d,name: %s\n", temp->id, unit->nickname);
}

S_list *find_id(unsigned id) {
    S_list *p1;
    p1 = head;
    unsigned rows = 1, cols = 1;
    while (id > 10) {
        id -= 10;
        rows++;
    }
    cols = id;
    p1 = head;
    while (p1->rows != rows)
        p1 = p1->down;
    while (p1->cols != cols)
        p1 = p1->right;
    /*remember to control the id in specific situation means 0*/
    return p1;
}

char *get_name(unsigned id) {
    if (id <= idnow)
        if(find_id(id)->value!=NULL)
            return (find_id(id)->value->nickname);
        else
            return NULL;
}

void delete_user(unsigned id) {
    S_user *unit;
    unit = (find_id(id)->value);
    strcat(unit->id,"(delete)");
}

/*if no return 0,if have return 1*/
void change_name_l0(unsigned id, char *str) {
    if (find_id(id) != NULL) {
        strcpy(get_name(id), str);
        printf("%s", get_name(id));
    } else
        printf("THERE IS NO such a user.\n");
}
