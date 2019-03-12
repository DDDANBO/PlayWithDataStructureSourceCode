#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int SElemType; /* SElemType���͸���ʵ������������������Ϊint */


/* ��ջ�ṹ */
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

Status visit(SElemType c);/* ��ӡ��ջ */ 
Status InitStack(LinkStack *S);/*  ����һ����ջS */
Status ClearStack(LinkStack *S);/* ��S��Ϊ��ջ */
Status StackEmpty(LinkStack S);/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
int StackLength(LinkStack S);/* ����S��Ԫ�ظ�������ջ�ĳ��� */
Status GetTop(LinkStack S,SElemType *e);/* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
Status Push(LinkStack *S,SElemType e);/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Pop(LinkStack *S,SElemType *e);/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status StackTraverse(LinkStack S);/* ������ջ */

int main()
{
	int j;
	LinkStack s;
	int e;
	if(InitStack(&s)==OK)	//�ж��Ƿ�ɹ�������ջ 
		for(j=1; j<=10; j++)
			Push(&s,j); 	//��ջ 
	printf("ջ��Ԫ������Ϊ��");
	StackTraverse(s);		// ������ջ
	Pop(&s,&e); 			//��ջ 
	printf("������ջ��Ԫ�� e=%d\n",e);
	printf("ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));	//�ж��Ƿ�Ϊ��ջ 
	GetTop(s,&e);			//����ջ��Ԫ�� 
	printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n",e,StackLength(s));	//����ջ�� 
	ClearStack(&s);			//���ջ 
	printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
	return 0;
}


Status visit(SElemType c)/* ��ӡ��ջ */
{
	printf("%d ",c);
	return OK;
}

/*  ����һ����ջS */
Status InitStack(LinkStack *S)
{
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!S->top)		//��������ڴ�ʧ�� 
		return ERROR;
	S->top=NULL;
	S->count=0;
	return OK;
}

/* ��S��Ϊ��ջ */
Status ClearStack(LinkStack *S)
{
	LinkStackPtr p,q;
	p=S->top;	//pΪջ��ָ�룬p�ǿ�ָ�룬q����ָ�� 
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	S->count=0;
	return OK;
}

/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
Status StackEmpty(LinkStack S)
{
	if (S.count==0)
		return TRUE;
	else
		return FALSE;
}

/* ����S��Ԫ�ظ�������ջ�ĳ��� */
int StackLength(LinkStack S)
{
	return S.count;
}

/* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
Status GetTop(LinkStack S,SElemType *e)
{
	if (S.top==NULL)
		return ERROR;
	else
		*e=S.top->data;
	return OK;
}

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Push(LinkStack *S,SElemType e)
{
	LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode));
	s->data=e;
	s->next=S->top;	/* �ѵ�ǰ��ջ��Ԫ�ظ�ֵ���½���ֱ�Ӻ�̣���ͼ�Т� */
	S->top=s;         /* ���µĽ��s��ֵ��ջ��ָ�룬��ͼ�Т� */
	S->count++;
	return OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status Pop(LinkStack *S,SElemType *e)
{
	LinkStackPtr p;
	if(StackEmpty(*S))
		return ERROR;
	*e=S->top->data;			// ��ջ��Ԫ�ظ���e 
	p=S->top;					/* ��ջ����㸳ֵ��p����ͼ�Т� */
	S->top=S->top->next;    /* ʹ��ջ��ָ������һλ��ָ���һ��㣬��ͼ�Т� */
	free(p);                    /* �ͷŽ��p */
	S->count--;					// ջ���Լ� 
	return OK;
}

Status StackTraverse(LinkStack S)/* ������ջ */ 
{
	LinkStackPtr p;
	p=S.top;	// SΪ�ṹ�壬�ṹ���ԱΪtop��count����topΪ�ṹ��ָ�룬ָ�����data��next�Ľṹ�� 
	while(p)
	{
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}


