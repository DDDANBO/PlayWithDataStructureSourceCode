#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */


/* 链栈结构 */
typedef struct StackNode
{
	SElemType data;
	struct StackNode *next;
} StackNode,*LinkStackPtr;


typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
} LinkStack;

Status visit(SElemType c);/* 打印链栈 */ 
Status InitStack(LinkStack *S);/*  构造一个空栈S */
Status ClearStack(LinkStack *S);/* 把S置为空栈 */
Status StackEmpty(LinkStack S);/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
int StackLength(LinkStack S);/* 返回S的元素个数，即栈的长度 */
Status GetTop(LinkStack S,SElemType *e);/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status Push(LinkStack *S,SElemType e);/* 插入元素e为新的栈顶元素 */
Status Pop(LinkStack *S,SElemType *e);/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status StackTraverse(LinkStack S);/* 遍历链栈 */

int main()
{
	int j;
	LinkStack s;
	int e;
	if(InitStack(&s)==OK)	//判断是否成功建立空栈 
		for(j=1; j<=10; j++)
			Push(&s,j); 	//进栈 
	printf("栈中元素依次为：");
	StackTraverse(s);		// 遍历链栈
	Pop(&s,&e); 			//出栈 
	printf("弹出的栈顶元素 e=%d\n",e);
	printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));	//判断是否为空栈 
	GetTop(s,&e);			//返回栈顶元素 
	printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));	//返回栈长 
	ClearStack(&s);			//清空栈 
	printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
	return 0;
}


Status visit(SElemType c)/* 打印链栈 */
{
	printf("%d ",c);
	return OK;
}

/*  构造一个空栈S */
Status InitStack(LinkStack *S)
{
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!S->top)		//如果分配内存失败 
		return ERROR;
	S->top=NULL;
	S->count=0;
	return OK;
}

/* 把S置为空栈 */
Status ClearStack(LinkStack *S)
{
	LinkStackPtr p,q;
	p=S->top;	//p为栈顶指针，p是快指针，q是慢指针 
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	S->count=0;
	return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(LinkStack S)
{
	if (S.count==0)
		return TRUE;
	else
		return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(LinkStack S)
{
	return S.count;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status GetTop(LinkStack S,SElemType *e)
{
	if (S.top==NULL)
		return ERROR;
	else
		*e=S.top->data;
	return OK;
}

/* 插入元素e为新的栈顶元素 */
Status Push(LinkStack *S,SElemType e)
{
	LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode));
	s->data=e;
	s->next=S->top;	/* 把当前的栈顶元素赋值给新结点的直接后继，见图中① */
	S->top=s;         /* 将新的结点s赋值给栈顶指针，见图中② */
	S->count++;
	return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(LinkStack *S,SElemType *e)
{
	LinkStackPtr p;
	if(StackEmpty(*S))
		return ERROR;
	*e=S->top->data;			// 将栈顶元素赋给e 
	p=S->top;					/* 将栈顶结点赋值给p，见图中③ */
	S->top=S->top->next;    /* 使得栈顶指针下移一位，指向后一结点，见图中④ */
	free(p);                    /* 释放结点p */
	S->count--;					// 栈长自减 
	return OK;
}

Status StackTraverse(LinkStack S)/* 遍历链栈 */ 
{
	LinkStackPtr p;
	p=S.top;	// S为结构体，结构体成员为top和count，而top为结构体指针，指向包含data和next的结构体 
	while(p)
	{
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}


