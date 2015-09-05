#include<stdio.h>
#include<stdlib.h>

//����ptr ��λ�ṹ�� 
#define LIST_ENTRY(ptr,type,member) (type*)((char*)ptr - (unsigned int)( &( ((type*)0)->member ) ))

//����˫���� 
#define FOR_LIST_EACH(pos,head) for(pos=(head)->next;pos!=(head);pos=pos->next)

//�����ַ���ΪʲôҪ�У� 
#define LIST_HEAD_INIT(name) {&(name),&(name)}

#define LIST_HEAD(name) struct qlist name = LIST_HEAD_INIT(name)

//����ʱ��ʼ�� 
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

//��new_p�嵽pre��next֮�� 
static void __qlist_add(struct qlist *new_p,struct qlist *pre,struct qlist *next){
	next->pre = new_p;
	new_p->next = next;
	new_p->pre = pre;
	pre->next = new_p;
}

//��ͷ���� 
static void qlist_add(struct qlist *new_p,struct qlist *head){
	__qlist_add(new_p,head,head->next);
}

//��β���� 
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
