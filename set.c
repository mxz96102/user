#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWSET (set *)malloc(sizeof(set))
#define NEWCHILD (child *)malloc(sizeof(child))

/*struct create*/
typedef struct child{
    unsigned child_id;
    struct child*next;
} child;

typedef struct set{
    unsigned type;
    unsigned id;
    char nickname[255];
    child *friend;
    child *follow;
    struct set*next;
} set;

/*extern function in data*/
extern void create_user(unsigned id,char name[]);
extern char* get_name(unsigned id);
unsigned check_name(char name[]);
extern  void create_list();
extern void delete_user(unsigned id);
extern void change_name_l0(unsigned id,char *str);
unsigned now_id=1;

/*local function */

/*local var*/
set *nowset,*headset;


/*start now*/

/*here is the function I create a set*/
/*0 id void and id also 0*/
/*1for we already have this name,0 is for complete*/


unsigned create_set(char *name){
    set *temp;
    unsigned l=0;
    if(now_id==1)
        create_list();
    l=check_name(name);
    if(l==1){
        printf("user exist\n");
        return 1;
    }
    temp=NEWSET;
    if(headset==NULL)
        headset=temp;
    if(nowset!=NULL)
        nowset->next=temp;
    nowset=temp;
    temp->id=now_id;
    strcpy(temp->nickname,name);
    create_user(now_id,name);
    now_id++;
    return 0;
}

unsigned get_nowid(){
    return now_id;
}

set *find(unsigned id){
    set *p1;
    p1=headset;

    while(p1->next!=NULL&&p1->id!=id){
        p1=p1->next;
    }
    return p1;
}

void getname(char*str,unsigned id){
    strcpy(str,get_name(id));
}

void add_friend(unsigned id, unsigned childid){
    child *temp,*c;
    set *p;
    temp=NEWCHILD;
    temp->child_id=childid;
    p=find(id);
    c=p->friend;
    while(c!=NULL) {
        if(c->child_id==childid){
            printf("Friend exits!\n");
            return;
        }
        c = c->next;
    }
    if(p->friend==NULL)
        p->friend=temp;
    else{
        c=p->friend;
        while(c->next!=NULL)
            c=c->next;
        c->next=temp;
    }

}

void add_follow(unsigned id, unsigned childid){
    child *temp,*c;
    set *p;
    temp=NEWCHILD;
    temp->child_id=childid;
    p=find(id);
    c=p->follow;
    while(c!=NULL) {
        if(c->child_id==childid){
            printf("Follow exits!\n");
            return;
        }
        c = c->next;
    }
    if(p->follow==NULL)
        p->follow=temp;
    else{
        c=p->follow;
        while(c->next!=NULL)
            c=c->next;
        c->next=temp;
    }
}

void delete_friend(unsigned id, unsigned childid) {
    child *c, *cpre;
    set *p;
    p = find(id);
    c = p->friend;
    while (c != NULL) {
        if (c->child_id == childid) {
            if (p->friend == c) {
                p->friend = NULL;
                free(c);
            } else {
                cpre->next = c->next;
                free(c);
            }
            printf("DELETE COMPLETE.");
            return;
        }
        cpre = c;
        c = c->next;
    }
    printf("friend not found!");
}

void delete_follow(unsigned id, unsigned childid) {
    child *c, *cpre;
    set *p;
    p = find(id);
    c = p->follow;
    while (c != NULL) {
        if (c->child_id == childid) {
            if (p->follow == c) {
                p->follow = NULL;
                free(c);
            } else {
                cpre->next = c->next;
                free(c);
            }
            printf("DELETE COMPLETE.");
            return;
        }
        cpre = c;
        c = c->next;
    }
    printf("friend not found!");
}

unsigned getlong(child *set1){
    unsigned i=0;
    while (set1!=NULL){
        set1=set1->next;
        i++;
    }
    return i;
}

void setcross(child *set1,child *set2,char *str){
    child *head,*p;
    p=set1;
    strcpy(str," ");
    while(p!=NULL){
        head=set2;

        while(head!=NULL){
            if(head->child_id==p->child_id)
                strcat(str," ");
                strcat(str,get_name(p->child_id));
            head=head->next;
        }
        p=p->next;
    }
}

void setadd(child *set1,child *set2,char *str) {
    child *head, *p;
    head = set1;
    strcpy(str," ");
    while (head != NULL) {
        strcat(str, " ");
        strcat(str, get_name(head->child_id));
        head = head->next;
    }
    head = set2;
    while (head != NULL) {
        p = set1;
        while (p != NULL) {
            if (head->child_id == p->child_id) {
                break;
            }
            p = p->next;
        }

        if (p == NULL) {
            strcat(str, " ");
            strcat(str, get_name(head->child_id));
        }
        head = head->next;
    }
}


void setcom(child *set1,child *set2,char *str){
    child *head, *p;
    head = set2;
    strcpy(str," ");
    while (head != NULL) {
        p = set1;
        while (p != NULL) {
            if (head->child_id == p->child_id) {
                break;
            }
            p = p->next;
        }

        if (p == NULL) {
            strcat(str, " ");
            strcat(str, get_name(head->child_id));
        }
        head = head->next;
    }

}

void get_fans(unsigned id,char *s){
    set *p;
    child *value;
    char fans[1000]="";
    p=headset;
    while(p!=NULL){
        value=p->follow;
        if(value!=NULL&&value->child_id==id) {
            strcat(fans, get_name(p->id));
            value = value->next;
        }
        p=p->next;
    }
    strcpy(s,fans);
}

void get_same_fans(unsigned id1,unsigned id2,char *s){
    set *p;
    child *value;
    char fans[1000]="";
    int flag=0;
    p=headset;
    while(p!=NULL){
        value=p->follow;
        if(value!=NULL&&(value->child_id==id1||value->child_id==id2)) {
            value = value->next;
            flag++;
        }
        if(flag==2)
            strcat(fans, get_name(p->id));
        p=p->next;
    }
    strcpy(s,fans);
}

void *get_follow(unsigned id){
    return find(id)->follow;
}

void *get_friend(unsigned id){
    return find(id)->friend;
}

void delete_set(unsigned id){
    set *p1,*p2;
    delete_user(id);
    p1=find(id);
    if(find(id)==headset){
        headset=find(id+1);
        free(p1);

    } else {
        p1 = find(id);
        p2 = find(id-1);
        p2->next=p1->next;
        free(p1);
    }
}

void change_name(unsigned id,char *name){
    change_name_l0(id,name);
    strcpy(find(id)->nickname,name);
}

unsigned out_to_array(int f[],child *p){
    unsigned i=0;
    while(f[i]!=0){
        f[i]=0;
        i++;
    }
    i=0;
    while(p!=NULL){
        f[i]=p->child_id;
        i++;
        p=p->next;
    }
    return i;
}

unsigned check_name(char name[]){
        int i=1;
        while(i<now_id){
            if(!strcmp(name,get_name(i))){
                return 1;
            }
            i++;
        }
    return 0;
}
