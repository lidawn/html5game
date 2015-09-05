#include<stdio.h>
#include<stdlib.h>

#define list_entry(ptr,type,member) (type*)((char*)ptr - (unsigned int)(&((type*)0->member)))

#define for_list_each(ptr,type) for(ptr=type->member;ptr!=ptr->next;ptr=ptr->next)

#define LIST_HEAD_INIT(name) {&(name),&(name)}

#define LIST_HEAD(name) struct qlist name = LIST_HEAD_INIT(name)

//运行时初始化 
#define INIT_LIST_HEAD(ptr) do{\
	(ptr)->next = (ptr);\
	(ptr)->pre = (ptr);\
}while(0) 

struct qlist{
	struct qlist *pre,*next;
};

struct my_list{
	struct qlist head;
	int value;
};

static void qlist_add(struct qlist *new,struct qlist *head){
	struct qlist *tmp = head->next;
	head->next = new;
	head->next->pre = new;
	new->next = tmp;
	new->pre = head;
}


int main(){
	struct my_list *test;
	struct my_list *tmp; 
	int i=0;
	test = (struct my_list*)malloc(sizeof(struct my_list));
	test->value = 1;
	
	INIT_LIST_HEAD(&(test->head));
	
	/*
	for(i=0;i<5;i++){
		tmp = (struct my_list*)malloc(sizeof(struct my_list));
		tmp->value = i+2;
		list_init(tmp->head);
		qlist_add(tmp->head,test->head);
	}
	*/
	
	return 0;
}
