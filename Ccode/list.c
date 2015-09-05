#include<stdio.h>
#include<stdlib.h>

//根据ptr 定位结构体 
#define LIST_ENTRY(ptr,type,member) (type*)((char*)ptr - (unsigned int)( &( ((type*)0)->member ) ))

//遍历双链表 
#define FOR_LIST_EACH(pos,head) for(pos=(head)->next;pos!=(head);pos=pos->next)

//这两种方法为什么要有？ 
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

//将new_p插到pre和next之间 
static void __qlist_add(struct qlist *new_p,struct qlist *pre,struct qlist *next){
	next->pre = new_p;
	new_p->next = next;
	new_p->pre = pre;
	pre->next = new_p;
}

//表头插入 
static void qlist_add(struct qlist *new_p,struct qlist *head){
	__qlist_add(new_p,head,head->next);
}

//表尾插入 
static void qlist_add_tail(struct qlist *new_p,struct qlist *head){
	__qlist_add(new_p,head->pre,head); 
}



int main(){
	struct my_list *tmp,*tail; 
	struct qlist *head_link,*link;
	int i=0;
	
	head_link = (struct qlist*)malloc(sizeof(struct qlist));
	INIT_LIST_HEAD(head_link);
	
	for(i=0;i<5;i++){
		tmp = (struct my_list*)malloc(sizeof(struct my_list));
		tmp->value = i;
		INIT_LIST_HEAD(&(tmp->head));
		qlist_add(&(tmp->head),head_link);
	}
	
	FOR_LIST_EACH(link,head_link){
		tail = LIST_ENTRY(link,struct my_list,head);
		printf("%d\n",tail->value);
	}
	
	return 0;
}
