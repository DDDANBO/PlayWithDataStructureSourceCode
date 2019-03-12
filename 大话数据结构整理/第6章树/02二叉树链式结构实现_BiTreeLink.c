#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */
#define ClearBiTree DestroyBiTree

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

/* ���ڹ��������********************************** */
int Index=1;
typedef char String[24]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */
String str;

typedef char TElemType;
TElemType Nil=' '; /* �ַ����Կո��Ϊ�� */

typedef struct BiTNode  /* ���ṹ */
{
	TElemType data;		/* ������� */
	struct BiTNode *lchild,*rchild; /* ���Һ���ָ�� */
} BiTNode,*BiTree;


Status StrAssign(String T,char *chars);
Status visit(TElemType e);
Status InitBiTree(BiTree *T);/* ����ն�����T */
void DestroyBiTree(BiTree *T);/* ��ʼ����: ������T���ڡ��������: ���ٶ�����T */
void CreateBiTree(BiTree *T);/* ��ǰ������������н���ֵ��һ���ַ���, #��ʾ������������������ʾ������T�� */
Status BiTreeEmpty(BiTree T);/* ��ʼ����: ������T���� , �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
int BiTreeDepth(BiTree T);/* ��ʼ����: ������T���ڡ��������: ����T����� */
TElemType Root(BiTree T);/* ��ʼ����: ������T���ڡ��������: ����T�ĸ� */
TElemType Value(BiTree p);/* ��ʼ����: ������T���ڣ�pָ��T��ĳ����� , �������: ����p��ָ����ֵ */
void Assign(BiTree p,TElemType value);/* ��p��ָ��㸳ֵΪvalue */
void PreOrderTraverse(BiTree T);/* ��ʼ����: ������T���� , �������: ǰ��ݹ����T */
void InOrderTraverse(BiTree T);/* ��ʼ����: ������T���� , �������: ����ݹ����T */
void PostOrderTraverse(BiTree T);/* ��ʼ����: ������T���� , �������: ����ݹ����T */


int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);


	StrAssign(str,"ABDH#K###E##CFI###G#J##");

	CreateBiTree(&T);

	printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	e1=Root(T);
	printf("�������ĸ�Ϊ: %c\n",e1);

	printf("\nǰ�����������:");
	PreOrderTraverse(T);
	printf("\n�������������:");
	InOrderTraverse(T);
	printf("\n�������������:");
	PostOrderTraverse(T);
	ClearBiTree(&T);
	printf("\n�����������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T);
	if(!i)
		printf("���գ��޸�\n");

	return 0;
}

Status StrAssign(String T,char *chars)
{
	int i;
	if(strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{
		T[0]=strlen(chars);
		for(i=1; i<=T[0]; i++)
			T[i]=*(chars+i-1);
		return OK;
	}
}

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

/* ����ն�����T */
Status InitBiTree(BiTree *T)
{
	*T=NULL;
	return OK;
}

/* ��ʼ����: ������T���ڡ��������: ���ٶ�����T */
void DestroyBiTree(BiTree *T)
{
	if(*T)
	{
		if((*T)->lchild) /* ������ */
			DestroyBiTree(&(*T)->lchild); /* ������������ */
		if((*T)->rchild) /* ���Һ��� */
			DestroyBiTree(&(*T)->rchild); /* �����Һ������� */
		free(*T); /* �ͷŸ���� */
		*T=NULL; /* ��ָ�븳0 */
	}
}

/* ��ǰ������������н���ֵ��һ���ַ��� */
/* #��ʾ������������������ʾ������T�� */
void CreateBiTree(BiTree *T)
{
	TElemType ch;

	/* scanf("%c",&ch); */
	ch=str[Index++];

	if(ch=='#')
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=ch; /* ���ɸ���� */
		CreateBiTree(&(*T)->lchild); /* ���������� */
		CreateBiTree(&(*T)->rchild); /* ���������� */
	}
}

/* ��ʼ����: ������T���� */
/* �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
Status BiTreeEmpty(BiTree T)
{
	if(T)
		return FALSE;
	else
		return TRUE;
}

/* ��ʼ����: ������T���ڡ��������: ����T����� */
int BiTreeDepth(BiTree T)
{
	int i,j;
	if(!T)
		return 0;
	if(T->lchild)
		i=BiTreeDepth(T->lchild);
	else
		i=0;
	if(T->rchild)
		j=BiTreeDepth(T->rchild);
	else
		j=0;
	return i>j?i+1:j+1;
}

/* ��ʼ����: ������T���ڡ��������: ����T�ĸ� */
TElemType Root(BiTree T)
{
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

/* ��ʼ����: ������T���ڣ�pָ��T��ĳ����� */
/* �������: ����p��ָ����ֵ */
TElemType Value(BiTree p)
{
	return p->data;
}

/* ��p��ָ��㸳ֵΪvalue */
void Assign(BiTree p,TElemType value)
{
	p->data=value;
}

/* ��ʼ����: ������T���� */
/* �������: ǰ��ݹ����T */
void PreOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	printf("%c",T->data);/* ��ʾ������ݣ����Ը���Ϊ�����Խ����� */
	PreOrderTraverse(T->lchild); /* ��������������� */
	PreOrderTraverse(T->rchild); /* ���������������� */
}

/* ��ʼ����: ������T���� */
/* �������: ����ݹ����T */
void InOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	InOrderTraverse(T->lchild); /* ������������� */
	printf("%c",T->data);/* ��ʾ������ݣ����Ը���Ϊ�����Խ����� */
	InOrderTraverse(T->rchild); /* ���������������� */
}

/* ��ʼ����: ������T���� */
/* �������: ����ݹ����T */
void PostOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	PostOrderTraverse(T->lchild); /* �Ⱥ������������  */
	PostOrderTraverse(T->rchild); /* �ٺ������������  */
	printf("%c",T->data);/* ��ʾ������ݣ����Ը���Ϊ�����Խ����� */
}

