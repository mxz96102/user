#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
/*struct create*/
typedef struct child{
    unsigned child_id;
    struct child*next;
} child;

typedef struct set{
    unsigned id;
    char nickname[255];
    child *friend;
    child *follow;
    struct set*next;
} set;
/*extern function here*/

extern unsigned create_set(char *name);
extern void add_friend(unsigned id, unsigned childid);
extern void add_follow(unsigned id, unsigned childid);
extern void get_fans(unsigned id,char *s);
extern void *get_follow(unsigned id);
extern void *get_friend(unsigned id);
extern void setcross(child *set1,child *set2,char *str);
extern void setadd(child *set1,child *set2,char *str);
extern void setcom(child *set1,child *set2,char *str);
extern unsigned get_nowid();
extern void getname(char*str,unsigned id);
extern void get_same_fans(unsigned id1,unsigned id2,char *s);
extern void delete_friend(unsigned id, unsigned childid);
extern void delete_follow(unsigned id, unsigned childid);
extern void delete_set(unsigned id);
extern unsigned out_to_array(int f[],child *p);
extern void change_name(unsigned id,char *name);

void create(char *name){
    unsigned l;
    l=create_set(name);
    if(l==1)
        printf("failed\n");
    else
    printf("Create compelete.\n");
}

void delete(unsigned id){
    delete_set(id);
}

unsigned get_totalid(){
    return get_nowid()-1;
}

void print_user(unsigned id){
    char temp[1000];
    printf("###############");
    getname(temp,id);
    printf("\nuser id:%d\n",id);
    printf("user name:");
    fputs(temp,stdout);
    printf("\nfollow:\n");
    setadd(get_follow(id),get_follow(id),temp);
    fputs(temp,stdout);
    printf("\nfriend:\n");
    setadd(get_friend(id),get_friend(id),temp);
    fputs(temp,stdout);
    printf("\nfans:\n");
    get_fans(id,temp);
    fputs(temp,stdout);
    printf("\n###############\n");
    printf("\n");
}

void follow(unsigned id, unsigned bid){
    add_follow(id,bid);
}

void friend(unsigned id, unsigned bid){
    add_friend(id,bid);
}

void same_friend(unsigned id1, unsigned id2){
    char temp[1000];
    setcross(get_friend(id1),get_friend(id2),temp);
    fputs(temp,stdout);
    printf("\n");
}

void same_follow(unsigned id1, unsigned id2){
    char temp[1000];
    setcross(get_follow(id1),get_follow(id2),temp);
    fputs(temp,stdout);
    printf("\n");
}

void same_fans(unsigned id1, unsigned id2){
    char temp[1000];
    get_same_fans(id1,id2,temp);
    fputs(temp,stdout);
    printf("\n");
}

void re_friend(unsigned id1, unsigned id2){
    char temp[1000];
    setcom(get_follow(id1),get_follow(id2),temp);
    fputs(temp,stdout);
    printf("\n");
}

void de_follow(unsigned id1, unsigned id2){
    delete_follow(id1,id2);
}

void de_friends(unsigned id1, unsigned id2){
    delete_friend(id1,id2);
}

void del_user(unsigned id){
    delete_set(id);
}

void change(unsigned id){
    char name[255];
    fgets(name,255,stdin);
    change_name(id,name);
}

void file_out_put(){
    FILE*fp;
    cJSON *root,*layer1,*layer2;
    char name[255],*str,i=0;
    unsigned id=1,f[255]={0},num=0;
    fp=fopen("users.json","w");
    root=cJSON_CreateArray();
    while(id<=get_totalid()){
        getname(name,id);
        layer1=cJSON_CreateObject();
        cJSON_AddItemToArray(root,layer1);\
        cJSON_AddNumberToObject(layer1,"id",id);
        cJSON_AddStringToObject(layer1,"name",name);
        num=out_to_array(f,get_follow(id));
        layer2=cJSON_CreateIntArray(f,num);
        cJSON_AddItemToObject(layer1,"followings",layer2);
        num=out_to_array(f,get_friend(id));
        layer2=cJSON_CreateIntArray(f,num);
        cJSON_AddItemToObject(layer1,"friends",layer2);
        id++;
    }
    str=cJSON_Print(root);
    printf("%s",str);
    fputs(str,fp);
    fclose(fp);
    cJSON_Delete(root);
}

void file_in_put(){
    FILE *fp;
    unsigned id=0,childid;
    int sum,i,j,k;
    char *str,name[255],*s;
    cJSON *root,*layer1,*layer2;

    fp=fopen("users.json","r");
    if(fp==NULL){
        printf("file error");
        return;
    }
    fseek(fp,0,SEEK_END);
    unsigned len=ftell(fp);
    s=(char *)malloc(len+1);
    rewind(fp);
    fread(s,1,len,fp);
    s[len]=0;
    root=cJSON_Parse(s);
    if(!root)
        printf("parse error");
    sum=cJSON_GetArraySize(root);
    while(id<sum&&sum!=0) {
        layer1 = cJSON_GetArrayItem(root, id);
        layer2 = cJSON_GetObjectItem(layer1, "name");
        str = layer2->valuestring;
        create(str);
        id++;
    }
    id=0;
    k=0;
    sum=cJSON_GetArraySize(root);
    while(k<sum) {
      layer1 = cJSON_GetArrayItem(root, id);
      layer2 = cJSON_GetObjectItem(layer1, "followings");
      j = cJSON_GetArraySize(layer2);
      i = 0;
        id=cJSON_GetObjectItem(layer1,"id")->valueint;
      while (i < j) {
          childid = (cJSON_GetArrayItem(layer2, i)->valueint);
          follow(id, childid);
          i++;
      }
      layer2 = cJSON_GetObjectItem(layer1, "friends");
      j = cJSON_GetArraySize(layer2);
      i = 0;
      while (i < j) {
          childid = cJSON_GetArrayItem(layer2, i)->valueint;
          friend(id, childid);
          i++;
      }
      k++;
  }

    fclose(fp);
    cJSON_Delete(root);
}
