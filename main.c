#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void create(char *name);
extern void follow(unsigned id, unsigned bid);
extern print_user(unsigned id);
extern void friend(unsigned id, unsigned bid);
extern void same_friend(unsigned id1, unsigned id2);
extern void same_follow(unsigned id1, unsigned id2);
extern unsigned get_totalid();
extern void file_out_put();
extern void file_in_put();
extern void follow(unsigned id, unsigned bid);
extern void friend(unsigned id, unsigned bid);
extern void same_fans(unsigned id1, unsigned id2);
extern void re_friend(unsigned id1, unsigned id2);
extern void de_follow(unsigned id1, unsigned id2);
extern void de_friends(unsigned id1, unsigned id2);
extern void del_user(unsigned id);
extern void user_create();
extern void delete(unsigned id);
extern void change(unsigned id);
void user_operation();
void file_operation();

int main(void) {
    unsigned totalid;
    unsigned m1 = 0, id;
    printf("####################\n"
                   "#  Welcome to\t\t#\n"
                   "#\tuser\t\t\t#\n"
                   "#\tmanagement\t\t#\n"
                   "#\tsystem\t\t\t#\n"
                   "####################\n");
    totalid = get_totalid();
    printf("Now we have %d user", totalid);
    while (m1 != 4) {
        m1=0;
        printf("Now ,what can I do for you ?\n"
                       "1.create a user\n2.file operation\n");
        totalid = get_totalid();
        if (totalid != 0)
            printf("3.check a user information\n");
        printf("4.exit\n");
        if(m1!=5)
        if (!(scanf("%d", &m1))) {
            printf("input error\n");
            exit(1);
        }
        switch (m1) {
            case 1:
                user_create();
                break;
            case 3:
                user_operation();
                break;
            case 2:
                file_operation();
                break;
            case 4:
                break;
            default:
                printf("I don't understand!");
                m1=5;
                break;
        }
    }

}


void user_operation(){
    int id,childid,op;
    char name[255];
    printf("please input the id you want:");
    fscanf(stdin,"%d",&id);
    if(id<=get_totalid())
        print_user(id);
    else {
        printf("not such a user!\n");
        user_operation();
    }
    while(op!=0) {
        printf("what can i do for you:\n");
        printf("1.find same user follow by id \t"
                       "2.find same friend by id\n"
                       "3.find the friend another user have(with out this user.\n"
                       "4.change the user nickname; \t"
                       "5.delete it\n"
                       "6.find same fans  \t"
                       "7.follow user by id.\n"
                       "8.friend user by id.  \t"
                       "9.remove follow\n"
                       "10.remove friend  \t"
                       "0.go back\n");
        scanf("%d\n", &op);
        switch (op) {
            case 1:
                scanf("%d", &childid);
                same_follow(id, childid);
                break;
            case 2:
                scanf("%d", &childid);
                same_friend(id, childid);
                break;
            case 3:
                scanf("%d", &childid);
                re_friend(id, childid);
                break;
            case 4:
                change(id);
                break;
            case 5:
                delete(id);
                break;
            case 6:
                scanf("%d", &childid);
                same_fans(id, childid);
                break;
            case 7:
                scanf("%d", &childid);
                follow(id, childid);
                break;
            case 8:
                scanf("%d", &childid);
                friend(id, childid);
                break;
            case 9:
                scanf("%d", &childid);
                de_follow(id, childid);
                break;
            case 10:
                scanf("%d", &childid);
                de_friends(id, childid);
                break;
            case 0:
                break;
                return;
            default:
                printf("I don't understand!\n");
                return;
        }
    }
}

void file_operation(){
    int i=0;
    printf("what can i do ?\n");
    printf("1.output to file.\n"
                   "2.input by file.\n");
    fscanf(stdin,"%d",&i);
    switch (i){
        case 1:
            file_out_put();
            break;
        case 2:
            file_in_put();
            break;
        default:
            break;
    }
}

void user_create(){
    char name[255];
    printf("please input your name:\n");
    if (!(scanf("%s", name))) {
        printf("input error");
        return;
    }
    create(name);
    return;
}
