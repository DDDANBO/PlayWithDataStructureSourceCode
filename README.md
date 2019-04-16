[TOC]





# 第一章	常用算法杂项





# 第二章	C语言程序设计





# 第三章	数据结构基本操作



## 预定义常量和类型

```c++
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status是函数的类型，其值是函数结果状态代码

typedef int Status;
typedef int ElemType;
```



## Visit遍历函数

```c++
Status Visit(ElemType c)
{
	printf("%d ",c);
	return OK;
}
```



## 自定义Scanf函数

>自定义的数据录入函数，用于从文件fp中读取格式化的输入。
>与fscanf不同之处在于此函数只会读取西文字符，对于中文字符，则会跳过。 



### 形参部分可以使用省略号

> ==C++==允许定义形参个数和类型不确定的函数。例如，C语言中的标准函数printf便使用这种机制。在声明不确定形参的函数时，==形参部分可以使用省略号“…”代替。==“…”告诉编译器，在函数调用时不检查形参类型是否与实参类型相同，也不检查参数个数。
>
> 即省略参数：用省略号…表示, ==省略号出现的地方可以有任意个任意类型的参数。==例如常用的printf函数：
> int printf (const char *format,   …); 



### 引用 <stdarg.h> 头文件的va_list、va_start、va_arg、va_end

>  例如：
>  void ConnectData(int i,...);
>  在上面的代码中，编译器只检查第一个参数是否为整型，而不对其他参数进行检查。
>  对于可变参数的函数，需要进行特殊的处理。首先需要==引用 <stdarg.h> 头文件==，然后利用va_list类型和va_start、va_arg、va_end 3个宏读取传递到函数中的参数值。  
>
>  ```c++
>  #include <stdarg.h>							//提供宏va_list、va_start、va_arg、va_end
>  ```
>  
>
>  这几个宏的定义如下（在 ANSI C 中）：
>
>  ```c++
>  type va_arg( va_list arg_ptr, type );
>  void va_end( va_list arg_ptr );
>  void va_start( va_list arg_ptr, prev_param ); 
>  ```
>
>  #### va_start函数
>
>  va_start函数将参数arg_ptr设置为可变参数列表的第一个参数。参数arg_ptr的类型必须为va_list。参数prev_param是在可变参数列表之前的那一个参数。（也就是说在 ANSI C 中，如果一个函数有可变参数，那么在该可变参数前必须有一个明确定义的参数，否则无法调用函数 va_start ，例如函数 int add(int i,...）是合法的，而函数 int add(...)是不合法的。）
>
>  
>
>  #### va_arg函数
>
>  va_arg函数将返回 arg_ptr 所指位置的值，并将 arg_ptr 指向下一个参数
>
>  
>
>  #### va_end函数
>
>  检索完所有参数后，va_end将指针重置为NULL。







```c++
int Scanf(FILE *fp, char *format, ...)
{
	int *i;
	char *ch, *s;
	float *f;
	int count, k, len, n;		
	int tmp;
	va_list ap;
	
	len = strlen(format);
	
	va_start(ap, format);
	
	for(count=0,k=2; k<=len; k=k+2)
	{
		while((tmp=getc(fp))!=EOF)			//跳过所有非西文字符 
		{
			if((tmp>=0 && tmp<=127))
			{
				ungetc(tmp, fp);			//遇到首个西文字符，将此西文字符放入输入流 
				break;
			}
		}
		
		if(tmp==EOF)
			break;
		
		if(format[k-1]=='c')				//读取字符		 
		{
			ch = va_arg(ap, char*);
						
			if(tmp!=EOF)
				count += fscanf(fp, "%c", ch);					
		}	
		
		if(format[k-1]=='d')				//读取整型 
		{
			i = va_arg(ap, int*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+')
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%d", i);
		}

		if(format[k-1]=='f')				//读取浮点型 
		{
			f = va_arg(ap, float*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+'|| tmp=='.' )
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%f", f);
		}
		
		if(format[k-1]=='s')				//读取字符串 
		{
			s = va_arg(ap, char*);
			
			while((tmp=getc(fp))!=EOF && (!isprint(tmp) || tmp==' '))
				;
			
			n = 0;
			if(!feof(fp))
			{
				ungetc(tmp, fp);
				while((tmp=getc(fp))!=EOF)
				{
					if(isprint(tmp) && tmp!=' ')
						s[n++] = tmp;
					else
						break;	
				}
				ungetc(tmp, fp);			
			}
                                                                                
			s[n] = '\0';
					
			count++;		
		}		
	}
		
	va_end(ap);
	
	return count;
}
```






## 顺序线性表（数组）



### 类型定义

```c++
typedef struct
{
	ElemType data[MAXSIZE];        /* 数组，存储数据元素 */
	int length;                                /* 线性表当前长度 */
}SqList;
```



### 初始化顺序线性表

```c++
Status InitList(SqList *L) 
{ 
    L->length=0;
    return OK;
}
```



### 判断顺序表是否为空

```c++
Status ListEmpty(SqList L)
{ 
	if(L.length==0)
		return TRUE;
	else
		return FALSE;
}
```



### 清空顺序表

```c++
Status ClearList(SqList *L)
{ 
    L->length=0;
    return OK;
}
```



### 计算顺序表的长度

```c++
int ListLength(SqList L)
{
	return L.length;
}
```



### 用e返回L中第i个数据元素的值

```c++
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
            return ERROR;
    *e=L.data[i-1];

    return OK;
}
```



### 返回L中第1个与e满足关系的数据元素的位序

```c++
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0)
            return 0;
    for(i=0;i<L.length;i++)
    {
            if (L.data[i]==e)
                    break;
    }
    if(i>=L.length)
            return 0;

    return i+1;
}
```



### 在L中第i个位置之前插入新的数据元素e

```c++
Status ListInsert(SqList *L,int i,ElemType e)
{ 
	int k;
	if (L->length==MAXSIZE)  /* 顺序线性表已经满 */
		return ERROR;
	if (i<1 || i>L->length+1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;

	if (i<=L->length)        /* 若插入数据位置不在表尾 */
	{
		for(k=L->length-1;k>=i-1;k--)  /* 将要插入位置之后的数据元素向后移动一位 */
			L->data[k+1]=L->data[k];
	}
	L->data[i-1]=e;          /* 将新元素插入 */
	L->length++;

	return OK;
}
```



### 删除L的第i个数据元素，并用e返回其值

```c++
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
    int k;
    if (L->length==0)               /* 线性表为空 */
		return ERROR;
    if (i<1 || i>L->length)         /* 删除位置不正确 */
        return ERROR;
    *e=L->data[i-1];
    if (i<L->length)                /* 如果删除不是最后位置 */
    {
        for(k=i;k<L->length;k++)/* 将删除位置后继元素前移 */
			L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}
```



### 遍历顺序线性表

```c++
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
            visit(L.data[i]);
    printf("\n");
    return OK;
}
```



### 合并La、Lb两个顺序线性表

```c++
void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for (i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if (!LocateElem(*La,e))
			ListInsert(La,++La_len,e);
	}
}
```



## 静态链表（数组）



### 类型定义

```c++
typedef struct 
{
    ElemType data;
    int cur;  /* 游标(Cursor) ，为0时表示无指向 */
} Component,StaticLinkList[MAXSIZE];
```



###  将一维数组space中各分量链成一个备用链表，space[0].cur为头指针，"0"表示空指针 

```c++
Status InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<MAXSIZE-1; i++)  
		space[i].cur = i+1;
	space[MAXSIZE-1].cur = 0; /* 目前静态链表为空，最后一个元素的cur为0 */
	return OK;
}
```



### 若备用空间链表非空，则返回分配的结点下标，否则返回0

```c++
int Malloc_SSL(StaticLinkList space) 
{ 
	int i = space[0].cur;           		/* 当前数组第一个元素的cur存的值 */
	                                		/* 就是要返回的第一个备用空闲的下标 */
	if (space[0]. cur)         
	    space[0]. cur = space[i].cur;       /* 由于要拿出一个分量来使用了， */
	                                        /* 所以我们就得把它的下一个 */
	                                        /* 分量用来做备用 */
	return i;
}
```



### 将下标为k的空闲结点回收到备用链表

```c++
void Free_SSL(StaticLinkList space, int k) 
{  
    space[k].cur = space[0].cur;    /* 把第一个元素的cur值赋给要删除的分量cur */
    space[0].cur = k;               /* 把要删除的分量下标赋值给第一个元素的cur */
}
```



### 计算静态链表的长度

```c++
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}
```



### 在L中第i个元素之前插入新的数据元素e

```c++
Status ListInsert(StaticLinkList L, int i, ElemType e)   
{  
    int j, k, l;   
    k = MAXSIZE - 1;   /* 注意k首先是最后一个元素的下标 */
    if (i < 1 || i > ListLength(L) + 1)   
        return ERROR;   
    j = Malloc_SSL(L);   /* 获得空闲分量的下标 */
    if (j)   
    {   
		L[j].data = e;   /* 将数据赋值给此分量的data */
		for(l = 1; l <= i - 1; l++)   /* 找到第i个元素之前的位置 */
		   k = L[k].cur;           
		L[j].cur = L[k].cur;    /* 把第i个元素之前的cur赋值给新元素的cur */
		L[k].cur = j;           /* 把新元素的下标赋值给第i个元素之前元素的ur */
		return OK;   
    }   
    return ERROR;   
}
```



### 删除在L中第i个数据元素

```c++
Status ListDelete(StaticLinkList L, int i)   
{ 
    int j, k;   
    if (i < 1 || i > ListLength(L))   
        return ERROR;   
    k = MAXSIZE - 1;   
    for (j = 1; j <= i - 1; j++)   
        k = L[k].cur;   
    j = L[k].cur;   
    L[k].cur = L[j].cur;   
    Free_SSL(L, j);   
    return OK;   
} 
```



### 遍历静态链表

```c++
Status ListTraverse(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
            visit(L[i].data);
            i=L[i].cur;
            j++;
    }
    return j;
    printf("\n");
    return OK;
}
```





## 非循环单向线性表



### 类型定义

```c++

#define LIST_INIT_SIZE 100				//顺序表存储空间的初始分配量 
#define LISTINCREMENT  10				//顺序表存储空间的分配增量

typedef int LElemType_Sq;

typedef struct
{
	LElemType_Sq *elem;					//存储空间基址（指向第一个结点的指针） 
	int length;							//当前顺序表长度 
	int listsize;						//当前分配的存储容量 
}SqList;
```



### 初始化线性表

```c++
Status InitList_Sq(SqList *L)
{
	(*L).elem = (LElemType_Sq*)malloc(LIST_INIT_SIZE*sizeof(LElemType_Sq));
	if(!(*L).elem)
		exit(OVERFLOW); 				//分配内存失败

	(*L).length = 0;					//初始化顺序表长度为0
	(*L).listsize = LIST_INIT_SIZE;		//顺序表初始内存分配量

	return OK;							//初始化成功	 
} 
```



### 清空线性表

```c++
void ClearList_Sq(SqList *L)
{
	(*L).length = 0;
}
```



### 销毁线性表

```c++
void DestroyList_Sq(SqList *L)
{
	free((*L).elem);

	(*L).elem = NULL;					//释放内存后置空指针 
	(*L).length = 0;
	(*L).listsize = 0;
}
```



### 判断线性表是否为空

```c++
Status ListEmpty_Sq(SqList L)
{
	return 	L.length==0 ? TRUE : FALSE;
}
```



### 计算线性表的长度

```c++
int ListLength_Sq(SqList L)
{
	return L.length;	
}
```



### 用e接收顺序表L中第i个元素

```c++
Status GetElem_Sq(SqList L, int i, LElemType_Sq *e)
{ 
	if(i<1 || i>L.length)
		return ERROR;					//i值不合法
	else
		*e = L.elem[i-1];

	return OK;
}
```



### 返回顺序表L中首个与e满足Compare关系的元素位序

```c++
int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq))
{
	int i = 1;							//i的初值为第一个元素的位序
	
	while(i<=L.length && !Compare(e, L.elem[i-1]))
		++i;

	if(i<=L.length)
		return i;
	else
		return 0; 
}
```



### 用pre_e接收cur_e的前驱

```c++
Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e)
{
	int i = 1;
	
	if(L.elem[0]!=cur_e)				//第一个结点无前驱 
	{
		while(i<L.length && L.elem[i]!=cur_e)
			++i;
		
		if(i<L.length)
		{
			*pre_e = L.elem[i-1];
			return OK;
		}	
	}
			
	return ERROR;
}
```



### 用next_e接收cur_e的后继

```c++
Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e)
{
	int i = 0;
	
	while(i<L.length && L.elem[i]!=cur_e)
		++i;

	if(i<L.length-1)					//最后一个结点无后继 
	{
		*next_e = L.elem[i+1];	
		return OK;
	}

	return ERROR;
}
```



### 在顺序表L的第i个位置上插入e

```c++
Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e)
{
	LElemType_Sq *newbase; 
	LElemType_Sq *p, *q;

	if(i<1 || i>(*L).length+1)
		return ERROR;					//i值不合法

	if((*L).length >= (*L).listsize)	//若存储空间已满，需开辟新空间 
	{
		newbase = (LElemType_Sq*)realloc((*L).elem, ((*L).listsize+LISTINCREMENT)*sizeof(LElemType_Sq));
		if(!newbase)
			exit(OVERFLOW);

		(*L).elem = newbase;
		(*L).listsize += LISTINCREMENT;
	}
	
	q = &(*L).elem[i-1];				//q为插入位置 
	
	for(p=&(*L).elem[(*L).length-1]; p>=q; --p)
		*(p+1) = *p;					//插入位置及之后的元素右移 
	
	*q = e;								//插入e 
	(*L).length++;						//表长增1

	return OK; 
}
```



### 删除顺序表L上第i个位置的元素，并用e返回

```c++
Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e)
{
	LElemType_Sq *p, *q;
		
	if(i<1 || i>(*L).length)
		return ERROR;					//i值不合法
	
	p = &(*L).elem[i-1];				//p为被删除元素的位置 
	*e = *p;
	q = (*L).elem+(*L).length-1; 		//表尾元素位置 
	
	for(++p; p<=q; ++p)
		*(p-1) = *p;					//被删元素之后的元素左移 

	(*L).length--;						//表长减1

	return OK;
}
```



### 用visit函数访问顺序表L

```c++
Status ListTraverse_Sq(SqList L, void(Visit)(LElemType_Sq))
{
	int i;

	for(i=0; i<L.length; i++)
		Visit(L.elem[i]);
	
	return OK;
}
```





## 单向循环链表































## 顺序栈



### 类型定义

```c++

#define STACK_INIT_SIZE	100				//顺序栈存储空间的初始分配量
#define STACKINCREMENT	10 				//顺序栈存储空间的分配增量

typedef int SElemType_Sq;

typedef struct
{
	SElemType_Sq *base;				//在栈构造之前和销毁之后，base的值为NULL 
	SElemType_Sq *top;				//栈顶指针 
	int stacksize;					//当前已分配的存储空间，以元素为单位 
}SqStack;
```



### 栈的初始化

```c++
Status InitStack_Sq(SqStack &S)
{
 	S.base = (SElemType_Sq *)malloc(STACK_INIT_SIZE*sizeof(SElemType_Sq));
	if(!S.base)
		exit(OVERFLOW);
		
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	
	return OK;
} 

//*******************

Status InitStack_Sq(SqStack *S)
{
 	(*S).base = (SElemType_Sq *)malloc(STACK_INIT_SIZE*sizeof(SElemType_Sq));
	if(!(*S).base)
		exit(OVERFLOW);
		
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	
	return OK;
}
```



### 销毁栈

```c++
Status DestroyStack_Sq(SqStack &S)
{
	free(S.base);
	
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;
	
	return OK;
} 

//*******************

Status DestroyStack_Sq(SqStack *S)
{
	free((*S).base);
	
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	
	return OK;
} 
```



### 清空栈


```c++
Status ClearStack_Sq(SqStack &S)
{
	S.top = S.base;
	
	return OK;
} 

//*******************

Status ClearStack_Sq(SqStack *S)
{
	(*S).top = (*S).base;
	
	return OK;
} 
```



### 判断栈是否为空

```c++
Status StackEmpty_Sq(SqStack S)
{
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
} 

//*******************


```



### 计算栈的长度


```c++
int StackLength_Sq(SqStack S)
{
	return S.top - S.base;
} 

//*******************


```



### 得到栈顶元素


```c++
Status GetTop_Sq(SqStack S, SElemType_Sq &e)
{
	if(S.top==S.base)
		return ERROR;
		
	e = *(S.top - 1);							//并不破坏栈 
	
	return OK;

} 

//*******************

Status GetTop_Sq(SqStack S, SElemType_Sq *e)
{
	if(S.top==S.base)
		return ERROR;
		
	*e = *(S.top - 1);							//并不破坏栈 
	
	return OK;

} 
```



### 入栈


```c++
Status Push_Sq(SqStack &S, SElemType_Sq e)
{
	if(S.top-S.base>=S.stacksize)		//栈满，追加存储空间
	{
		S.base = (SElemType_Sq *)realloc(S.base, (S.stacksize+STACKINCREMENT)*sizeof(SElemType_Sq));
		if(!S.base)
			exit(OVERFLOW);						//存储分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	
	*(S.top) = e;								//进栈先赋值，栈顶指针再自增 
	(S.top)++;
	
	return OK;
} 

//*******************

Status Push_Sq(SqStack *S, SElemType_Sq e)
{
	if((*S).top-(*S).base>=(*S).stacksize)		//栈满，追加存储空间
	{
		(*S).base = (SElemType_Sq *)realloc((*S).base, ((*S).stacksize+STACKINCREMENT)*sizeof(SElemType_Sq));
		if(!(*S).base)
			exit(OVERFLOW);						//存储分配失败
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	
	*(S->top) = e;								//进栈先赋值，栈顶指针再自增 
	(S->top)++;

	return OK;
} 
```



### 出栈


```c++
Status Pop_Sq(SqStack &S, SElemType_Sq &e)
{
	if(S.top==S.base)
		return ERROR;

	S.top--;									//出栈栈顶指针先递减，再赋值 
	e = *(S.top);
	
	return OK;
} 

//*******************

Status Pop_Sq(SqStack *S, SElemType_Sq *e)
{
	if((*S).top==(*S).base)
		return ERROR;

	(*S).top--;									//出栈栈顶指针先递减，再赋值 
	*e = *((*S).top);

	return OK;
} 
```



### 遍历栈中元素


```c++
Status StackTraverse_Sq(SqStack S, void(Visit)(SElemType_Sq))
{												//遍历不应该破坏栈 
	SElemType_Sq *p = S.base;
	
	while(p<S.top)
		Visit(*p++);
	
	return OK;
}

//*******************


```









## 非循环队列



### 类型定义

```c++
typedef int QElemType_L;

typedef struct QNode				 
{
	QElemType_L data;
	struct QNode *next;
}QNode,* QueuePtr;

typedef struct
{
	QueuePtr front;					//头指针 
	QueuePtr rear;					//尾指针 
}LinkQueue;							//队列的链式存储表示
```



### 非循环队列的初始化

```c++
Status InitQueue_L(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);

	Q.front->next = NULL;

	return OK;
}

//*******************

Status InitQueue_L(LinkQueue *Q)
{
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(OVERFLOW);

	(*Q).front->next = NULL;

	return OK;
}
```



### 清空队列

```c++
void ClearQueue_L(LinkQueue &Q)
{
	Q.rear = Q.front->next;
	
	while(Q.rear)
	{
		Q.front->next = Q.rear->next;		
		free(Q.rear);		
		Q.rear = Q.front->next;
	}
	
	Q.rear = Q.front;
}

//*******************

void ClearQueue_L(LinkQueue *Q)
{
	(*Q).rear = (*Q).front->next;
	
	while((*Q).rear)
	{
		(*Q).front->next = (*Q).rear->next;		
		free((*Q).rear);		
		(*Q).rear = (*Q).front->next;
	}
	
	(*Q).rear = (*Q).front;
}
```



### 销毁队列


```c++
void DestroyQueue_L(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;	
	}
}

//*******************

void DestroyQueue_L(LinkQueue *Q)
{
	while((*Q).front)
	{
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;	
	}
}
```



### 判断队列是否为空


```c++
Status QueueEmpty_L(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
} 

//*******************


```



### 计算队列的长度


```c++
int QueueLength_L(LinkQueue Q)
{
	int count = 0;
	QueuePtr p = Q.front;
	
	while(p!=Q.rear)
	{
		count++;
		p = p->next;
	}
	
	return count;
} 

//*******************


```



### 得到队头元素


```c++
Status GetHead_L(LinkQueue Q, QElemType_L &e)
{
	QueuePtr p;
	
	if(Q.front==Q.rear)
		return ERROR;
		
	p = Q.front->next;
	e = p->data;
	
	return OK;
} 

//*******************

Status GetHead_L(LinkQueue Q, QElemType_L *e)
{
	QueuePtr p;
	
	if(Q.front==Q.rear)
		return ERROR;
		
	p = Q.front->next;
	*e = p->data;
	
	return OK;
} 
```



### 入队


```c++
Status EnQueue_L(LinkQueue &Q, QElemType_L e)
{
	QueuePtr p;
	
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);

	p->data = e;
	p->next = NULL;
	
	Q.rear->next = p;
	Q.rear=p;

	return OK;
} 

//*******************

Status EnQueue_L(LinkQueue *Q, QElemType_L e)
{
	QueuePtr p;
	
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);

	p->data = e;
	p->next = NULL;
	
	(*Q).rear->next = p;
	(*Q).rear=p;

	return OK;
} 
```



### 出队


```c++
Status DeQueue_L(LinkQueue &Q, QElemType_L &e)
{
	QueuePtr p;
	
	if(Q.front==Q.rear)
		return ERROR;
		
	p = Q.front->next;
	e = p->data;
	
	Q.front->next = p->next;
	if(Q.rear==p)
		Q.rear = Q.front;
		
	free(p);
	
	return OK;
} 

//*******************

Status DeQueue_L(LinkQueue *Q, QElemType_L *e)
{
	QueuePtr p;
	
	if((*Q).front==(*Q).rear)
		return ERROR;
		
	p = (*Q).front->next;
	*e = p->data;
	
	(*Q).front->next = p->next;
	if((*Q).rear==p)
		(*Q).rear = (*Q).front;
		
	free(p);
	
	return OK;
} 
```



### 遍历非循环队列


```c++
void QueueTraverse_L(LinkQueue Q, void (Visit)(QElemType_L))
{
	QueuePtr p;
	
	p = Q.front->next;
	
	while(p)
	{
		Visit(p->data);
		p = p->next;
	}
}

//*******************


```





## 循环队列（不设头指针）

>**假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意不设头指针）**



### 类型定义

```c++
typedef int QElemType_L;

typedef struct QNode				 
{
	QElemType_L data;
	struct QNode *next;
}QNode,* QueuePtr;

typedef struct
{
	QueuePtr rear;					//尾指针 
}LinkQueue;							//队列的链式存储表示
```





### 循环队列初始化

```c++
Status InitQueue_L(LinkQueue *Q)					//队列初始化 
{
	(*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).rear)
		exit(OVERFLOW);

	(*Q).rear->next = (*Q).rear;	//初次创建的(*Q).rear为头结点，且next指向
									//自身，达到循环效果。 

	return OK;
}
```



### 入队

```c++
Status EnQueue_L(LinkQueue *Q, QElemType e)	//入队 
{
	QueuePtr p;
	
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;

	p->next = (*Q).rear->next;	//入队后新结点的next始终指向头结点，构成循环队列 
	(*Q).rear->next = p;		//每次都在队尾入队 
	(*Q).rear = p;

	return OK;
} 
```



### 出队

```c++
Status DeQueue_L(LinkQueue *Q, QElemType *e)	//出队 
{
	QueuePtr h, p;
	
	h = (*Q).rear->next;
	if(h->next==(*Q).rear->next)
		return ERROR;
		
	p = h->next;
	*e = p->data;
	
	h->next = p->next;	//当队列只有一个元素时，头结点的next指向自身 
	
	if(p==(*Q).rear)							//队列只有一个元素 
		(*Q).rear = h;							//rear指向头结点 

	free(p);

	return OK;
}
```



### 遍历循环队列

```c++
void Output_L(LinkQueue Q)
{
	QueuePtr p;
	
	for(p=Q.rear->next->next; p!=Q.rear->next; p=p->next)
		printf("%d ", p->data);
}
```



## 循环队列（设头指针）

> **设置一个标志域tag，并以tag的值为0和1来区分，尾指针和头指针值相同时的队列状态是“空”还是“满”。**



### 类型定义

```c++
typedef int QElemType;

typedef struct
{
	QElemType *base;
	int front;	
	int rear;
	int tag;							//0表示空，1表示满 
}SqQueue;
```



### 队列初始化

```c++
Status InitQueue_L(SqQueue *Q)
{
	(*Q).base = (QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if(!((*Q).base))
		exit(OVERFLOW);
	
	(*Q).front = (*Q).rear = 0;
	(*Q).tag = 0;
}
```



### 入队

```c++
Status EnQueue_L(SqQueue *Q, QElemType e)
{
	if((*Q).rear==(*Q).front && (*Q).tag==1)	//队列满
		return ERROR;

	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear+1)%MAXQSIZE;

	if((*Q).rear==(*Q).front)					//入队后队满 
		(*Q).tag = 1;

	return OK;
}
```



### 出队

```c++
Status DeQueue_L(SqQueue *Q, QElemType *e)
{
	if((*Q).front==(*Q).rear && (*Q).tag==0)	//队列空
		return ERROR;

	*e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front+1)%MAXQSIZE;

	if((*Q).rear==(*Q).front)					//出队后队空 
		(*Q).tag = 0;

	return OK;
}
```



### 遍历队列

```c++
void Output_L(SqQueue Q)
{
	int i;
	
	for(i=Q.front; i!=Q.rear; i=(i+1)%MAXQSIZE)
		printf("%d ", Q.base[i]);
}
```





## 堆串

### 类型定义

```c++
/* 串的堆存储表示 */
typedef struct
{
	char *ch;							//若是非空串，则按串长分配存储区，否则ch为NULL 
	int length;
}HString;
```



### 初始化S为空串

```c++
void InitString_H(HString *S)
{
	(*S).ch = NULL;
	(*S).length = 0;
}
```



### 生成一个其值等于常量chars的串T

```c++
Status StrAssign_H(HString *T, char *chars)
{
	int i, j;
	
	InitString_H(T);	

	i = strlen(chars);

	if(!i)
		return ERROR;
	else
	{
		(*T).ch = (char*)malloc(i*sizeof(char));		
		if(!((*T).ch))
			exit(OVERFLOW);
			
		for(j=0; j<i; j++)
			(*T).ch[j] = chars[j];
			
		(*T).length = i;
	}

	return OK;
} 
```



### 由串S复制得到串T

```c++
Status StrCopy_H(HString *T, HString S)
{
	int i;
	
	InitString_H(T);
	
	if(StrEmpty_H(S))
		return ERROR;
		
	(*T).ch = (char*)malloc(S.length*sizeof(char));
	if(!(*T).ch)
		exit(OVERFLOW);
	
	for(i=0; i<S.length; i++)
		(*T).ch[i] = S.ch[i];
	
	(*T).length = S.length;

	return OK;
}
```



### 若S为空串，返回TRUE,否则返回FALSE

```c++
Status StrEmpty_H(HString S)
{
	if(S.length==0 && S.ch==NULL)
		return TRUE;
	else
		return FALSE;
}
```



### 若S>T，返回值>0；若S<T，返回值<0；否则，返回值=0

```c++
Status StrCompare_H(HString S, HString T)
{
	int i;
	
	for(i=0; i<S.length&&i<T.length; i++)
	{
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];	
	}

	return S.length-T.length;
}
```



### 求串长

```c++
int StrLength_H(HString S)
{
	if(StrEmpty_H(S))
		return 0;
	else
		return S.length;
}
```



### 清空串S

```c++
Status ClearString_H(HString *S)
{
	if((*S).ch)
	{
		free((*S).ch);
		(*S).ch = NULL;
	}

	(*S).length = 0;

	return OK;
}
```



### 用T返回由S1和S2联接而成的新串

```c++
Status Concat_H(HString *T, HString S1, HString S2)
{
	int i;
	
	InitString_H(T);
	
	(*T).length = S1.length + S2.length;
	
	(*T).ch = (char*)malloc((*T).length*sizeof(char));
	if(!(*T).ch)
		exit(OVERFLOW);
		
	for(i=0; i<S1.length; i++)
		(*T).ch[i] = S1.ch[i];
		
	for(i=0; i<S2.length; i++)
		(*T).ch[S1.length+i] = S2.ch[i];
	
	return OK;
}
```



### 用Sub返回串S的第pos个字符起长度为len的子串

```c++
Status SubString_H(HString *Sub, HString S, int pos, int len)
{
	int i;
	
	InitString_H(Sub);
	
	if(StrEmpty_H(S))
		return ERROR;

	if(pos<1 || pos>S.length || len<0 || pos+len-1>S.length)
		return ERROR;

	if(len)								//非空子串
	{
		(*Sub).ch = (char*)malloc(len*sizeof(char));
		if(!(*Sub).ch)
			exit(OVERFLOW);

		for(i=0; i<len; i++)
			(*Sub).ch[i] = S.ch[i+pos-1];

		(*Sub).length = len;
	}

	return OK;
}
```



### 返回T在S中第pos个字符后第一次出现的位置，不存在则返回0

```c++
int Index_H(HString S, HString T, int pos)
{
	int s, t, i;
	HString Sub;
	
	InitString_H(&Sub);

	if(pos>0)
	{
		s = S.length;
		t = T.length;
		i = pos;
		
		while(i+t-1<=s)
		{
			SubString_H(&Sub, S, i, t);

			if(StrCompare_H(Sub, T))
				i++;
			else
				return i;
		}
	}

	return 0;
}
```



### 用V替换主串S中出现的所有与T相等的不重叠的子串

```c++
Status Replace_H(HString *S, HString T, HString V)
{
	int i;
	
	if(StrEmpty_H(T))
		return ERROR;
		
	i = Index_H(*S, T, 1);

	while(i!=0)
	{
		StrDelete_H(S, i, StrLength_H(T));

		StrInsert_H(S, i, V);

		i += StrLength_H(V);

		i = Index_H(*S, T, i);
	}

	return OK;
}
```



### 在串S的第pos个字符之前插入串T

```c++
Status StrInsert_H(HString *S, int pos, HString T)
{
	int i;

	if(pos<1 || pos>(*S).length+1)
		return ERROR;

	if(StrEmpty_H(T))
		return ERROR;
	else
	{
		(*S).ch = (char*)realloc((*S).ch, ((*S).length+T.length)*sizeof(char));
		if(!(*S).ch)
			exit(OVERFLOW);

		for(i=(*S).length-1; i>=pos-1; i--)		//为插入T而腾出位置
			(*S).ch[i+T.length] = (*S).ch[i];

		for(i=0; i<T.length; i++)
			(*S).ch[pos-1+i] = T.ch[i]; 		//插入T

		(*S).length += T.length;
	}

	return OK; 
}
```



### 从串S中删除第pos个字符起长度为len的子串

```c++
Status StrDelete_H(HString *S, int pos, int len)
{
	int i;

	if(StrEmpty_H(*S))
		return ERROR;

	if(pos<1 || pos+len-1>(*S).length ||len<0)
		return ERROR;

	for(i=pos-1; i+len<=(*S).length; i++)
		(*S).ch[i] = (*S).ch[i+len];

	(*S).length -= len;

	(*S).ch = (char*)realloc((*S).ch, (*S).length*sizeof(char));	//缩小分配的空间 

	return OK;
}
```



### 销毁串S

```c++
void DestroyString_H(HString *S)
{
	//堆串不能被销毁
}
```



### 输出串S

```c++
void StrPrint_H(HString S)
{
	int i;

	if(StrEmpty_H(S))
		printf("S为空串，不可输出！");

	for(i=0; i<S.length; i++)
		printf("%c", S.ch[i]);
}
```





## 数组和广义表

### 类型定义

```c++
#define MAXSIZE 400							//假设非零元个数的最大值为400
```



### 三元组顺序表(稀疏矩阵)类型定义

```c++
typedef int MElemType_TSq;

typedef struct
{
	int i, j;								//该非零元的行下标和列下标 
	MElemType_TSq e;
}Triple;
typedef struct
{
	Triple data[MAXSIZE+1];					//非零元三元组表，data[0]未用
	int mu, nu, tu;							//矩阵的行数、列数和非零元个数
}TSMatrix;
```



### 创建n个矩阵

```c++
Status CreateSMatrix_T(FILE *fp, int n, ...)
{
	int count, k;
	TSMatrix *M;
	
	if(n<1)
		return ERROR;

	va_list ap;	
	va_start(ap, n);
	
	for(count=1; count<=n; count++)
	{
		M = va_arg(ap, TSMatrix*);
		
		Scanf(fp, "%d%d%d", &((*M).mu), &((*M).nu), &((*M).tu));

		for(k=1; k<=(*M).tu; k++)
			Scanf(fp, "%d%d%d", &((*M).data[k].i), &((*M).data[k].j), &((*M).data[k].e));
	}
	
	va_end(ap);
	
	return OK;	
}
```



### 销毁矩阵

```c++
void DestroySMatrix_T(TSMatrix *M)
{
	(*M).mu = 0;
	(*M).nu = 0;
	(*M).tu = 0;
}
```



### 输出矩阵

```c++
void PrintSMatrix_T(TSMatrix M)
{
	int r, c;
	int k = 1;
	
	for(r=1; r<=M.mu; r++)
	{
		for(c=1; c<=M.nu; c++)
		{
			if(r==M.data[k].i && c==M.data[k].j)
			{
				printf("%3d ", M.data[k].e);
				k++;
			}
			else
				printf("  0 ");
		}
		printf("\n");
	}	
}
```



### 矩阵的复制

```c++
void CopySMatrix_T(TSMatrix M, TSMatrix *T)
{
	(*T) = M;								//结构可以直接复制 
}
```



### 矩阵的加法Q = M + N

```c++
Status AddSMatri_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	int m, n, k;
	
	if(M.mu!=N.mu || M.nu!=N.nu)
	{
		printf("两矩阵不能相加！！\n");
		return ERROR;	
	}
	
	Q->mu = M.mu;
	Q->nu = M.nu;
	Q->tu = 0;
	m = n = k = 1;
	
	while(m<=M.tu && n<=N.tu)				//依次遍历M与N的三元组 
	{
		if(M.data[m].i<N.data[n].i)
		{
			Q->data[k] = M.data[m];
			m++;
		}
		else if(M.data[m].i>N.data[n].i)
		{
			Q->data[k] = N.data[n];
			n++;
		}
		else								//M.data[m].i==N.data[n].i
		{
			if(M.data[m].j<N.data[n].j)
			{
				Q->data[k] = M.data[m];
				m++;
			}
			else if(M.data[m].j>N.data[n].j)
			{
				Q->data[k] = N.data[n];
				n++;
			}
			else							//M.data[m].j==N.data[n].j
			{
				if(M.data[m].e+N.data[n].e)
				{
					Q->data[k].i = M.data[m].i;
					Q->data[k].j = M.data[m].j;
					Q->data[k].e = M.data[m].e + N.data[n].e;
					m++;
					n++;
				}
				else
				{
					m++;
					n++;
					continue;
				}		
			}
		}
		
		k++;
		Q->tu++;
	}
	
	while(m<=M.tu)
	{
		Q->data[k] = M.data[m];
		m++;
		k++;
		Q->tu++;
	}
	
	while(n<=N.tu)
	{
		Q->data[k] = N.data[n];
		n++;
		k++;
		Q->tu++;
	}
	
	return OK;
}
```



### 矩阵的减法Q = M - N

```c++
Status SubSMatrix_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	int m, n, k;
	
	if(M.mu!=N.mu || M.nu!=N.nu)
	{
		printf("两矩阵不能相减！！\n");
		return ERROR;	
	}
	
	Q->mu = M.mu;
	Q->nu = M.nu;
	Q->tu = 0;
	m = n = k = 1;
	
	while(m<=M.tu && n<=N.tu)
	{
		if(M.data[m].i<N.data[n].i)
		{
			Q->data[k] = M.data[m];
			m++;
		}		
		else if(M.data[m].i>N.data[n].i)
		{
			Q->data[k].i =  N.data[n].i;
			Q->data[k].j =  N.data[n].j;
			Q->data[k].e = -N.data[n].e;
			n++;
		}
		else								//M.data[m].i==N.data[n].i
		{
			if(M.data[m].j<N.data[n].j)
			{
				Q->data[k] = M.data[m];
				m++;
			}
			else if(M.data[m].j>N.data[n].j)
			{
				Q->data[k].i =  N.data[n].i;
				Q->data[k].j =  N.data[n].j;
				Q->data[k].e = -N.data[n].e;
				n++;
			}
			else							//M.data[m].j==N.data[n].j
			{
				if(M.data[m].e-N.data[n].e)
				{
					Q->data[k].i = M.data[m].i;
					Q->data[k].j = M.data[m].j;
					Q->data[k].e = M.data[m].e - N.data[n].e;
					m++;
					n++;
				}
				else
				{
					m++;
					n++;
					continue;
				}		
			}
		}
		
		k++;
		Q->tu++;
	}
	
	while(m<=M.tu)
	{
		Q->data[k] = M.data[m];
		m++;
		k++;
		Q->tu++;
	}
	
	while(n<=N.tu)
	{
		Q->data[k].i =  N.data[n].i;
		Q->data[k].j =  N.data[n].j;
		Q->data[k].e = -N.data[n].e;;
		n++;
		k++;
		Q->tu++;
	}
	
	return OK;	
}
```



### 矩阵的乘法Q = M * N

```c++
Status MultSMatrix_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	int m, n, i, j, k;
	MElemType_TSq c, c1, c2;
	
	if(M.nu!=N.mu)							//M列数等于N行数 
	{
		printf("两矩阵不能相乘！！\n");
		return ERROR;	
	}
	
	Q->mu = M.mu;							//Q初始化 
	Q->nu = N.nu;
	Q->tu = 0;
	
	if(M.tu*N.tu)							//Q是非零矩阵
	{
		for(i=1; i<=M.mu; i++)				//传统矩阵乘法 
		{
			for(j=1; j<=N.nu; j++)
			{
				c = 0;
				for(k=1; k<=M.nu; k++)
				{
					c1 = 0;
					for(m=1; m<=M.tu; m++)	//依次寻找位于指定位置的M三元组 
					{
						if(M.data[m].i==i && M.data[m].j==k)
						{
							c1 = M.data[m].e;
							break;
						}
					}
					
					c2 = 0;
					for(n=1; n<=N.tu; n++)	//依次寻找位于指定位置的N三元组
					{
						if(N.data[n].i==k && N.data[n].j==j)
						{
							c2 = N.data[n].e;
							break;
						}
					}
					
					if(c1 && c2)
						c += c1 * c2;	
				}
				
				if(c)
				{
					Q->tu++;
					Q->data[Q->tu].i = i;
					Q->data[Q->tu].j = j;
					Q->data[Q->tu].e = c;
				}			
			}
		}
	} 
	
	return OK;
}
```



### 矩阵转置

```c++
void TransposeSMatrix_T(TSMatrix M, TSMatrix *T)
{
	int p, q, col;
	
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	
	if(T->tu)
	{
		q = 1;									//q用于T中非零元计数 
		for(col=1; col<=M.nu; ++col)			//col代表M的列，T的行 
		{
			for(p=1; p<=M.tu; ++p)				//p用于M中非零元计数
			{
				if(M.data[p].j==col)
				{
					T->data[q].i = M.data[p].j;	//M的列变为T的行 
					T->data[q].j = M.data[p].i;	//M的行变为T的列
					T->data[q].e = M.data[p].e;	//每个三元组值不变
					++q; 
				}
			}
		}
	}
}
```



### 矩阵快速转置

```c++
void FastTransposeSMatrix_T(TSMatrix M, TSMatrix *T)
{
	int col, t, p, q;
	int num[M.nu];							//num[col]表示M第col列中非零元的个数 
	int copt[M.nu];							//copt[col]表示M第col列第一个非零元在T->data中恰当的位置 
	
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	
	if(T->tu)
	{
		for(col=1; col<=M.nu; ++col)
			num[col] = 0;					//初始化数组num
		
		for(t=1; t<=M.tu; ++t)				//t遍历M中三元组
			num[M.data[t].j]++;				//统计M中每列非零元个数
		
		copt[1] = 1;
		for(col=2; col<=M.nu; ++col)
			copt[col] = copt[col-1] + num[col-1];
		
		for(p=1; p<=M.tu; ++p)				//依次扫描M中的三元组 
		{
			col = M.data[p].j;				//col为M中第p个三元组中元素的列 
			q = copt[col];					//q为当前三元组元素在T中应放置的位置 
			T->data[q].i = M.data[p].j;
			T->data[q].j = M.data[p].i;
			T->data[q].e = M.data[p].e;
			++copt[col];					//再遇到此列元素时位置增一 
		}
	}
}
```





## 树和二叉树



## 1、二叉树（二叉链表存储）相关类型定义

```c++
typedef char TElemType;							//假设二叉树元素均为字符
typedef struct BiTNode
{
	TElemType data;								//结点元素 
	struct BiTNode* lchild;						//左孩子指针 
	struct BiTNode* rchild;						//右孩子指针 
}BiTNode;										//二叉树结点 
typedef BiTNode* BiTree;						//指向二叉树结点的指针
```



### 栈元素类型

```c++
typedef BiTree SElemType_Sq;					//重定义栈元素类型 
#include "../../▲03 栈和队列/01 SequenceStack/SequenceStack.c"	//**▲03 栈和队列**// 

要用到栈的类型定义
```



### 存储当前结点信息，按树结构打印树的时候使用

```c++
typedef struct									
{ 
	BiTree left;								//当前结点的左指针 
	BiTree right;								//当前结点的右指针 
	int n;										//当前结点的次序 
}Node;
```



### 构造空二叉树T (初始化二叉树)

```c++
void InitBiTree(BiTree *T)
{
	*T = NULL;
}
```



### 清空二叉树T

```c++
void ClearBiTree(BiTree *T)
{
	if(*T)												 		//二叉树不为空
	{
		if((*T)->lchild)										//清空左树 
			ClearBiTree(&((*T)->lchild));							
		if((*T)->rchild)										//清空右树 
			ClearBiTree(&((*T)->rchild));

		free(*T);												//释放根结点 
		
		*T = NULL;												//置空树指针 
	} 
}
```



### 销毁二叉树T

```c++
void DestroyBiTree(BiTree *T)
{
	//二叉树无法销毁 
}
```



### 判断二叉树T是否为空

```c++
Status BiTreeEmpty(BiTree T)
{
	return T==NULL ? TRUE : ERROR;
} 
```



### 按先序序列构造二叉树_1

```c++
Status CreateBiTree(FILE *fp, BiTree *T)
{
	char ch;

	Scanf(fp, "%c", &ch);
	
	if(ch == '^')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!(*T))
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree(fp, &(*T)->lchild);
		CreateBiTree(fp, &(*T)->rchild);
	}
	
	return OK;
}
```



### 按先序序列构造二叉树_2

```c++
BiTree f(FILE *fp, BiTree *T)
{
	char ch;

	Scanf(fp, "%c", &ch);
	
	if(ch == '^')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!(*T))
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree(fp, &(*T)->lchild);
		CreateBiTree(fp, &(*T)->rchild);
	}
}
```



### 返回二叉树长度（按完全二叉树计算）

```c++
int BiTreeLength(BiTree T)
{
	Node node[100];												//存储结点信息 
	int i, len;
	
	i = len = 0;
	
	if(T)
	{	
		node[i].left = T->lchild;
		node[i].right = T->rchild;
		node[i].n = 1;
		if(node[i].n>len)
			len = node[i].n;

		while(i>=0)
		{
			while(node[i].left)									//访问左子树 
			{
				node[i+1].left = node[i].left->lchild;
				node[i+1].right = node[i].left->rchild;
				node[i+1].n = 2*node[i].n;
				node[i].left = NULL;
				i++;
				if(node[i].n>len)
					len = node[i].n;
			}
			
			if(node[i].right)									//左子树为空时访问右子树 
			{
				node[i+1].left = node[i].right->lchild;
				node[i+1].right = node[i].right->rchild;
				node[i+1].n = 2*node[i].n+1;
				node[i].right = NULL;
				i++;
				if(node[i].n>len)
					len = node[i].n;
			}
			
			if(node[i].left==NULL && node[i].right==NULL)
				i--;
		}	
	}
	
	return len;
}
```



### 返回二叉树深度（层数）

```c++
int BiTreeDepth(BiTree T)
{
	int LD, RD;
	
	if(T==NULL)
		return 0;								//空树深度为0 
	else
	{
		LD = BiTreeDepth(T->lchild);			//求左子树深度 
		RD = BiTreeDepth(T->rchild);			//求右子树深度 
	
		return (LD>=RD?LD:RD)+1;
	}
}
```



### 用e返回二叉树的根结点值

```c++
Status Root(BiTree T, TElemType *e)
{
	if(!T)
		return ERROR;
	else
	{
		*e = T->data;
		return OK;
	}
} 
```



### 返回某结点的值，p为结点指针

```c++
TElemType Value(BiTree p)
{
	return p->data;
}
```



### 为某结点赋值，p为结点指针

```c++
void Assign(BiTree p, TElemType value)
{
	p->data = value;
}
```



### 返回某结点的双亲结点值

```c++
TElemType Parent(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;
	
	if(T==NULL || (T!=NULL && e==T->data))
		return '\0';
	
	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].lchild)
		{
			if(node[i].lchild->data==e)
				return node[i].data;
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].rchild)
		{
			if(node[i].rchild->data==e)
				return node[i].data;
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		
		if(node[i].lchild==NULL && node[i].rchild==NULL)
			i--;		
	}
	
	if(i<0)
		return '\0';	
}
```



### 返回某结点的左孩子结点值

```c++
TElemType LeftChild(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;

	if(!T)
		return '\0';
	
	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].data!=e && node[i].lchild)
		{
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].data==e)
		{
			if(node[i].lchild)
				return node[i].lchild->data;
			else
				return '\0';		
		}
		
		if(node[i].rchild)
		{
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
			
		if(node[i].lchild==NULL && node[i].rchild==NULL && node[i].data!=e)
			i--;		
	}
	
	if(i<0)
		return '\0';	
}
```



### 返回某结点的右孩子结点值

```c++
TElemType RightChild(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;

	if(!T)
		return '\0';
	
	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].data!=e && node[i].lchild)
		{
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].data==e)
		{
			if(node[i].rchild)
				return node[i].rchild->data;
			else
				return '\0';		
		}
		
		if(node[i].rchild)
		{
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}		
		if(node[i].lchild==NULL && node[i].rchild==NULL)
			i--;		
	}
	
	if(i<0)
		return '\0';
}
```



### 返回某结点的左兄弟结点值

```c++
TElemType LeftSibling(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;
	
	if(T==NULL || (T!=NULL && e==T->data))
		return '\0';
	
	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].rchild)
		{
			if(node[i].rchild->data==e)
			{
				if(node[i].lchild)
					return node[i].lchild->data;
				else
					return '\0';
			}
			
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		
		if(node[i].lchild)
		{
			if(node[i].lchild->data==e)
				return '\0';
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].lchild==NULL && node[i].rchild==NULL)
			i--;		
	}
	
	if(i<0)
		return '\0';
}
```



### 返回某结点的右兄弟结点值

```c++
TElemType RightSibling(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;
	
	if(T==NULL || (T!=NULL && e==T->data))
		return '\0';
	
	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].lchild)
		{
			if(node[i].lchild->data==e)
			{
				if(node[i].rchild)
					return node[i].rchild->data;
				else
					return '\0';
			}
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].rchild)
		{
			if(node[i].rchild->data==e)
				return '\0';
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		
		if(node[i].lchild==NULL && node[i].rchild==NULL)
			i--;		
	}
	
	if(i<0)
		return '\0';
}
```



### 获取指向结点e的指针_1

```c++
BiTree LocationBiTree_1(BiTree T, TElemType e)
{
	BiTNode node[100];
	int i = 0;
	
	if(T==NULL)
		return NULL;
	
	if(T->data==e)
		return T;

	node[i] = *T;
	
	while(i>=0)
	{
		while(node[i].lchild)
		{
			if(node[i].lchild->data==e)
				return node[i].lchild;
			node[i+1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		
		if(node[i].rchild)
		{
			if(node[i].rchild->data==e)
				return node[i].rchild;
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		
		if(node[i].lchild==NULL && node[i].rchild==NULL)
			i--;		
	}
	
	if(i<0)
		return NULL;
}
```



### 获取指向结点e的指针_2

```c++
BiTree LocationBiTree_2(BiTree T, TElemType e)
{
	BiTree p = NULL;
	
	if(T)
	{
		if(T->data==e)
			p = T;
		else
		{
			if(p=LocationBiTree_2(T->lchild, e))
				return p;
			
			if(p=LocationBiTree_2(T->rchild, e))
				return p;
		}
	}
	
	return p;
}
```



### 将树T0插入到树T中成为结点e的子树，LR为插入标记，T0只有左子树

```c++
Status InsertBiTree(BiTree T, TElemType e, BiTree T0, int LR)
{
	BiTree p = LocationBiTree_1(T, e);
	
	if(p)
	{
		T0->rchild = LR ? p->rchild : p->lchild;
		LR ? (p->rchild=T0) : (p->lchild=T0);
		
		return OK;
	}
	
	return ERROR;	
}
```



### 删除e结点的左子树或右子树，LR为删除标记

```c++
Status DeleteBiTree(BiTree T, TElemType e, int LR)
{
	BiTree p = LocationBiTree_2(T, e);
	
	if(p)
	{
		LR ? ClearBiTree(&(p->rchild)) : ClearBiTree(&(p->lchild));
		
		return OK;
	}
	
	return ERROR;
}
```



### 层序遍历二叉树_1（利用数组实现）

```c++
void LevelOrderTraverse_1(BiTree T, void(Visit)(TElemType))//用printf打印可以不用Visit函数
{
	int i, j;
	BiTree p[100];					//树指针数组，用来模拟队列
	
	i = j = 0;
	
	if(T)
		p[j++] = T;
		
	while(i<j)
	{
		Visit(p[i]->data);//或者	printf("%c ", p[i]->data);
		if(p[i]->lchild)
			p[j++] = p[i]->lchild;
		if(p[i]->rchild)
			p[j++] = p[i]->rchild;
		i++;		
	}
}
```



### 层序遍历二叉树_2（利用队列实现）

```c++
Status LevelOrderTraverse_2(BiTree T, Status (*visit)(TElemType e))
{
	BiTree p;
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	while (p || !QueueEmpty(Q))
	{
		if (p)
		{
			visit(p->data);
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else		//队列为空时，退出while循环
				break;
		}
	}
	return OK;
}
```





### 先序遍历二叉树_1（递归）

```c++
void PreOrderTraverse_1(BiTree T, void(Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse_1(T->lchild, Visit);
		PreOrderTraverse_1(T->rchild, Visit);
	}
}
```



### 先序遍历二叉树_2（递归）

```c++
Status PreOrderTraverse_2(BiTree T, Status(Visit)(TElemType))
{	
	if(T)
	{
		if(Visit(T->data))
		{
			PreOrderTraverse_2(T->lchild, Visit);
			PreOrderTraverse_2(T->rchild, Visit);	
		}
		return OK;
	}
	else
		return ERROR;
}
```



### 先序遍历二叉树_1（非递归）

```c++
void PreOrderTraverse_3(BiTree T)
{
	SqStack S;
	SElemType_Sq e;
	
	if(!BiTreeEmpty(T))
	{
		InitStack_Sq(&S);
		Push_Sq(&S, T);
		
		while(!StackEmpty_Sq(S))
		{
			GetTop_Sq(S, &e);
			printf("%c ", e->data);
			
			if(e->lchild)
				Push_Sq(&S, e->lchild);
			else
			{
				while(!StackEmpty_Sq(S))
				{
					Pop_Sq(&S, &e);
					
					if(e->rchild)
					{
						Push_Sq(&S, e->rchild);
						break;					
					}
				}
			}
		}
	}
}
```



### 先序遍历二叉树_2（非递归）

```c++
Status PreOrderTraverse_4(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)  	//访问根指针，左指针进栈
		{
			if (ERROR == visit(p->data))
				return ERROR;
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}
```





### 中序遍历二叉树_1（递归）

```c++
void InOrderTraverse_1(BiTree T, void(Visit)(TElemType))
{
	if(T)
	{
		InOrderTraverse_1(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse_1(T->rchild, Visit);
	}
}
```



### 中序遍历二叉树_2（非递归）

```c++
Status InOrderTraverse_2(BiTree T, Status(Visit)(TElemType))
{
	SqStack S;
	SElemType_Sq p;
	
	InitStack_Sq(&S);
	Push_Sq(&S, T);
	
	while(!StackEmpty_Sq(S))
	{
		while(GetTop_Sq(S, &p) && p)				//栈顶元素不为空
			Push_Sq(&S, p->lchild);					//向左走到尽头
			
		Pop_Sq(&S, &p);								//空指针退栈
		
		if(!StackEmpty_Sq(S))						//访问结点，向右一步 
		{
			Pop_Sq(&S, &p);
			if(!Visit(p->data))
				return ERROR;
			Push_Sq(&S, p->rchild);
		}  
	}
	return OK;	 
}
```



### 中序遍历二叉树_3（非递归）

```c++
Status InOrderTraverse_3(BiTree T, Status(Visit)(TElemType))
{
	SqStack S;
	SElemType_Sq p;
	
	InitStack_Sq(&S);
	p = T;
	
	while(p || !StackEmpty_Sq(S))
	{
		if(p)
		{
			Push_Sq(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop_Sq(&S, &p);
			if(!Visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	return OK;	
}
```



### 后序遍历二叉树（递归）

```c++
void PostOrderTraverse(BiTree T, void(Visit)(TElemType))
{
	if(T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T->data);
	}
}
```



### 后序遍历二叉树_1（非递归）

```c++
void PostOrderTraverse_1(BiTree T)
{
	SqStack S;
	BiTree p;
	SElemType_Sq e;
	int StackMark[100] = {};							//模拟栈，设置各结点访问标记 
	int k;

	InitStack_Sq(&S);
	p = T;
	k = -1;
		
	while(1)
	{
		while(p)
		{
			Push_Sq(&S, p);
			k++;
			StackMark[k] = 1;
			p = p->lchild;
		}
			
		while(!p && !StackEmpty_Sq(S))			//p为空但栈不为空 
		{
			GetTop_Sq(S, &p);
			
			if(StackMark[k]==1)				//已访问过一次，当前是第二次访问 
			{
				StackMark[k] = 2;				
				p = p->rchild;
			}
			else							//已访问过两次，当前是第三次访问 
			{
				printf("%c ", p->data);
				Pop_Sq(&S, &e);
				StackMark[k] = 0;
				k--;
				p = NULL;
			}
		}
		
		if(StackEmpty_Sq(S))
			break;
	}		
}
```



### 后序遍历二叉树_2（非递归）

```c++
Status PostOrderTraverse_2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];	//标志栈
	int t = 1;
	p = T;
	while (p || !StackEmpty(S))
	{
		while (p)  	//向左走到尽头
		{
			Push(S, p);
			p = p->lchild;
			Tag[t++] = 0;
		}

		while (!StackEmpty(S) && 1 == Tag[t-1])  	//结点标志为1表示右子树已经访问过
		{
			Pop(S, p);
			t--;
			if (ERROR == visit(p->data))
				return ERROR;
		}

		if (!StackEmpty(S))  	//结点标志为0，则访问右子树，并将结点标志置为1
		{
			Tag[t-1] = 1;
			GetTop(S, p);
			p = p->rchild;
		}
		else
			break;
	}

	return OK;
}
```





### 按二叉树的结构打印树

```c++
void PrintTree(BiTree T)
{
	int row, col;
	int i, j, m, l, r;
	BiTNode a[100][100] = {};					//用一个足够大的矩阵按原样存储树 
	
	if(T)
	{
		row = BiTreeDepth(T);					//总行数
		col = pow(2, row) - 1;					//总列数
		
		for(i=1; i<=row-1; i++)
		{
			for(j=1; j<=pow(2, i-1); j++)
			{
				m = (2*j-1)*pow(2, row-i);		//当前行结点相对位序 
				l = (4*j-3)*pow(2, row-i-1);	//下一行结点相对位序 
				r = (4*j-1)*pow(2, row-i-1);
				
				if(i==1)						//初始化 
					a[i][m] = *T;
				
				if(a[i][m].lchild)				//下一行 
					a[i+1][l] = *(a[i][m].lchild);
					
				if(a[i][m].rchild)				//下一行 
					a[i+1][r] = *(a[i][m].rchild);
			} 
		}
		
		for(i=1; i<=row; i++)
		{
			for(j=1; j<=col; j++)
			{
				if(a[i][j].data)
					printf("%c", a[i][j].data);
				else
					printf(" ");
			}
			printf("\n");
		}
	}
} 
```



### 求先序序列中第k个结点的值

```c++
Status Algo_6_41(BiTree T, TElemType *e, int *order, int k)	//order用来计数 
{
	if(T)
	{
		(*order)++;
		
		if(*order==k)
		{
			*e = T->data;		
			return OK;					
		}
		else
		{		
			if(Algo_6_41(T->lchild, e, order, k))
				return OK;
			if(Algo_6_41(T->rchild, e, order, k))
				return OK;
		}
	}
	
	return ERROR;
}
```



### 计算二叉树中叶子结点数目

```c++
int Algo_6_42(BiTree T)
{
	int count = 0;
	
	if(T)
	{
		if(T->lchild==NULL && T->rchild==NULL)
			count++;
		else
		{
			count += Algo_6_42(T->lchild);
			count += Algo_6_42(T->rchild);
		}	
	}
	
	return count;	 
}
```



### 交换二叉树的左右子树

```c++
void Algo_6_43(BiTree T)
{
	BiTree p;
	
	if(T)
	{
		p = T->lchild;
		T->lchild = T->rchild;
		T->rchild = p;

		Algo_6_43(T->lchild);
		Algo_6_43(T->rchild);
	}
}
```



### 求二叉树中以结点'x'为根的子树的深度

```c++
int Algo_6_44(BiTree T, TElemType x)
{
	 BiTree p;
	 
	 p = LocationBiTree_2(T, x);			//第一个递归求出x的位置，以指针形式返回
	 //LocationBiTree_2(获取指向结点e的指针_2)
	 return BiTreeDepth(p);				//第二个递归求出子树x的深度 
}
```



### 删除元素值为'x'的结点（可能不止一个）及其子树

```c++
void Algo_6_45(BiTree *T, TElemType x)
{
	if(*T)
	{
		if((*T)->data==x)
			ClearBiTree(T);						//递归清空子树 
		else
		{
			Algo_6_45(&((*T)->lchild), x);		//递归向左右子树寻找 
			Algo_6_45(&((*T)->rchild), x);
		}
	}
}
```



### 复制二叉树的非递归算法

```c++
void Algo_6_46(BiTree T, BiTree *Tx)
{
	SqStack ST, STx;
	SElemType_Sq e;
	BiTree p, q;
	 
	if(!BiTreeEmpty(T))
	{
		InitStack_Sq(&ST);
		InitStack_Sq(&STx);
		
		Push_Sq(&ST, T);
		p = (BiTree)malloc(sizeof(BiTNode));
		if(!p)
			exit(OVERFLOW);
		p->data = T->data;
		*Tx = p;
		Push_Sq(&STx, *Tx);
		
		while(!StackEmpty_Sq(ST))
		{
			GetTop_Sq(ST, &e);
			GetTop_Sq(STx, &q);
			
			if(e->lchild)								//向左访问 
			{
				Push_Sq(&ST, e->lchild);
				p = (BiTree)malloc(sizeof(BiTNode));
				if(!p)
					exit(OVERFLOW);
				p->data = e->lchild->data;
				q->lchild = p;
				Push_Sq(&STx, q->lchild);			
			}
			else										//向右访问并回退 
			{
				q->lchild = NULL;
				while(!StackEmpty_Sq(ST))
				{
					Pop_Sq(&ST, &e);
					Pop_Sq(&STx, &q);
										
					if(e->rchild)
					{	
						Push_Sq(&ST, e->rchild);
						p = (BiTree)malloc(sizeof(BiTNode));
						if(!p)
							exit(OVERFLOW);
						p->data = e->rchild->data;
						q->rchild = p;
						Push_Sq(&STx, q->rchild);						
						break;					
					}
					else
						q->rchild = NULL;				
				}
			}
		}
	}
}
```



### 遍历树寻找根结点到p结点的路径，path存储路径上各结点指针

```c++
Status FindPath_6_48(BiTree T, TElemType p, BiTree path[100])
{
	BiTNode node[100];
	int i = 0;
	
	if(T==NULL)
		return ERROR;
	
	path[i] = T;
	node[i] = *T;
		
	while(i>=0)
	{
		while(node[i].lchild || path[i]->data==p)
		{
			if(path[i]->data==p)						//寻路成功 
				return OK;
			else
			{
				path[i+1] = node[i].lchild;
				node[i+1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;			
			}
		}
		
		if(node[i].rchild)
		{
			path[i+1] = node[i].rchild;
			node[i+1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		else
		{
			path[i] = NULL;
			i--;
		}		
	}
	
	if(i<0)												//寻路失败 
		return ERROR;
}
```



### 求两结点的共同祖先

```c++
BiTree Algo_6_48(BiTree T, TElemType p, TElemType q)		//p、q设为具体的元素，原理不变 
{
	BiTree path_1[100] = {};
	BiTree path_2[100] = {}; 
	int k, x;
	
	if(FindPath_6_48(T, p, path_1) && FindPath_6_48(T, q, path_2))	//借助于路径寻找函数 
	{	
		k = 0;
		if(path_1[k]->data!=p && path_2[k]->data!=q)
		{
			while(path_1[k]->data==path_2[k]->data)
				k++;
			
			return path_1[k-1];		
		}
	}

	return NULL;
}
```



### 判断二叉树是否为完全二叉树

```c++
Status Algo_6_49(BiTree T)
{
	int i, j;
	BiTree p[100] = {};					//树指针数组，模拟队列 
	int order[100] = {}; 
	
	i = j = 0;
	
	if(T)								//遍历的同时为各结点编号 
	{
		p[j] = T;	
		order[j] = 1;
		j++;
		
		while(i<j)
		{
			if(i>0 && order[i]>order[i-1]+1)
				return ERROR;			//若结点序号不连续，则非完全二叉树 
				
			if(p[i]->lchild)
			{
				p[j] = p[i]->lchild;
				order[j] = 2*order[i];
				j++;			
			}

			if(p[i]->rchild)
			{
				p[j] = p[i]->rchild;
				order[j] = 2*order[i]+1;
				j++;
			}
			
			i++;		
		}
	}
	
	return OK;
} 
```



## 2、树的二叉链表（孩子-兄弟）类型定义

```c++
typedef char TElemType_CS;						//假设树中元素均为字符
typedef struct CSNode
{
	TElemType_CS data;
	struct CSNode* firstchild;					//指向孩子
	struct CSNode* nextsibling;					//指向兄弟 
}CSNode;
typedef CSNode* CSTree;
```



### 自定义栈元素类型

```c++
typedef CSTree SElemType_Sq;
#include "../../▲03 栈和队列/01 SequenceStack/SequenceStack.c"	//**▲03 栈和队列**// 

要用到栈的定义
```



### 构造空树T (初始化树)

```c++
void InitTree_CS(CSTree *T)
{
	*T = NULL;
}
```



### 清空树T

```c++
void ClearTree_CS(CSTree *T)
{
	if(*T)
	{
		if((*T)->firstchild)
			ClearTree_CS(&(*T)->firstchild);
		if((*T)->nextsibling)
			ClearTree_CS(&(*T)->nextsibling);

		free(*T);												//释放根结点 
		
		*T = NULL;
	}
}
```



### 销毁树T

```c++
void DestroyTree_CS(CSTree *T)
{
	//此存储结构二叉树无法销毁 
}
```



### 判断树T是否为空

```c++
Status TreeEmpty_CS(CSTree T)
{
	return T==NULL ? TRUE : ERROR;
} 
```



### 按先序序列构造树

```c++
Status CreateTree_CS(FILE *fp, CSTree *T)
{
	char ch;
							
	Scanf(fp, "%c", &ch);
	
	if(ch == '^')
		*T = NULL;
	else
	{
		*T = (CSTree)malloc(sizeof(CSNode));
		if(!(*T))
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateTree_CS(fp, &(*T)->firstchild);
		CreateTree_CS(fp, &(*T)->nextsibling);
	}
	
	return OK;
}
```



### 返回树的度

```c++
int TreeDegree_CS(CSTree T)
{
	int i, j, max, tmp;
	CSTree Q[100];									//临时存放各结点 
	
	i = j = 0;
	max = -1;
	
	if(T)
	{
		max = 0;
		Q[j++] = T->firstchild;

		while(i<j)									//按层序遍历 
		{
			tmp = 0;
			
			while(Q[i])
			{
				tmp++;	
				
				if(Q[i]->firstchild)				//存储有孩子的结点 
					Q[j++] = Q[i]->firstchild;
				
				Q[i] = Q[i]->nextsibling;			//统计本层结点个数 
			}
			
			if(tmp>max)
				max = tmp;
			
			i++;
		}
	}
	
	return max;	
}
```



### 返回树的深度

```c++
int TreeDepth_CS(CSTree T)
{
	int row, max;
	SqStack S;
	CSTree tmp;
	
	row = 0;
	
	if(T)
	{
		InitStack_Sq(&S);
		Push_Sq(&S, T);
		row = max = 1;
		
		while(!StackEmpty_Sq(S))
		{
			GetTop_Sq(S, &tmp);
			
			while(tmp->firstchild)
			{
				Push_Sq(&S, tmp->firstchild);
				max++;
				if(row<max)
					row = max;
				GetTop_Sq(S, &tmp);			
			}
			
			Pop_Sq(&S, &tmp);
			
			if(tmp->nextsibling)
				Push_Sq(&S, tmp->nextsibling);		
			else
			{
				while(!StackEmpty_Sq(S))
				{
					Pop_Sq(&S, &tmp);
					max--;
														
					if(tmp->nextsibling)
					{
						Push_Sq(&S, tmp->nextsibling);
						break;
					}				
				}
			}
		}	
	}
	
	return row;
}
```



### 返回树的根结点值

```c++
TElemType_CS Root_CS(CSTree T)
{
	if(T)
		return T->data;
	else
		return '\0';
}
```



### 返回树中第i个结点值（按层序计数）

```c++
TElemType_CS Value_CS(CSTree T, int i)
{
	int m, n, count;
	CSTree Q[100];
	
	if(T && i>0)
	{
		m = n = 0;
		count = 0;	
		Q[n++] = T;		
		
		while(m<n)
		{
			while(Q[m])
			{
				count++;
				if(count==i)
					return Q[m]->data;
					
				if(Q[m]->firstchild)
					Q[n++] = Q[m]->firstchild;
				
				Q[m] = Q[m]->nextsibling;
			}
				
			m++;
		}
	}
	
	return '\0';	
}
```



### 返回指向结点e的指针，NULL代表无此结点

```c++
CSTree Order_CS(CSTree T, TElemType_CS e)
{
	int i, j, count;
	CSTree Q[100];
	
	i = j = 0;
	
	if(T)
	{
		Q[j++] = T;
		
		while(i<j)
		{
			while(Q[i] && Q[i]->data!=e)
			{
				if(Q[i]->firstchild)
					Q[j++] = Q[i]->firstchild;
				
				Q[i] = Q[i]->nextsibling;
			}
			
			if(Q[i] && Q[i]->data==e)
				return Q[i];
				
			i++;
		}
	}
	
	return NULL;	
}
```



### 替换结点e的值为value

```c++
Status Assign_CS(CSTree T, TElemType_CS e, TElemType_CS value)
{
	int i, j, count;
	CSTree p;
	
	p = Order_CS(T, e);
		
	if(p)								//找到了e
	{
		p->data = value;
		return OK;
	} 

	return ERROR;
}
```



### 返回结点e的第order个孩子的值（从左至右计数）

```c++
TElemType_CS ChildValue_CS(CSTree T, TElemType_CS e, int order)
{
	int i, j, count;
	CSTree Q[100];
	
	count = -1;
	i = j = 0;
	
	if(T)
	{
		Q[j++] = T;
		
		while(i<j)
		{
			while(Q[i] && Q[i]->data!=e)
			{
				if(Q[i]->firstchild)
					Q[j++] = Q[i]->firstchild;
				
				Q[i] = Q[i]->nextsibling;
			}
			
			if(Q[i] && Q[i]->data==e)
				break;
				
			i++;
		}
		
		if(i<j)								//找到了p
		{
			count = 0;
			if(Q[i]->firstchild)
			{
				Q[i] = Q[i]->firstchild;
				while(Q[i])
				{
					count++;
					if(count==order)
						return Q[i]->data;
					Q[i] = Q[i]->nextsibling;
				}
			}
		} 
	}
	
	return '\0';	
}
```



### 返回元素e的左（右）兄弟，mark标记左右

```c++
TElemType_CS Sibling_CS(CSTree T, TElemType_CS e, int mark)
{
	int i, j, m, n;
	CSTree Q[100];
	TElemType_CS key[100] = {};									//将最左边的结点记录下来 
	
	i = j = 0;
	m = n = 0;
	
	if(T && T->data!=e)
	{
		Q[j++] = T;
		key[n++] = T->data;
		
		while(i<j)
		{
			while(Q[i])
			{
				
				if(Q[i]->firstchild)
				{
					Q[j++] = Q[i]->firstchild;
					key[n++] = Q[i]->firstchild->data;				
				}
				
				if(mark==0)
				{
					if(Q[i]->data==e && Q[i]->data==key[m])
						return '\0';
					
					if(Q[i]->nextsibling && Q[i]->nextsibling->data==e)
						return Q[i]->data;
				}
				else
				{
					if(Q[i]->data==e && Q[i]->nextsibling)
						return Q[i]->nextsibling->data;
				}
				
				Q[i] = Q[i]->nextsibling;			
			}
			
			i++;
			m++;
		}		
	}
	
	return '\0';
}
```



### 返回结点p的孩子结点（子树）个数，返回负数代表结点p不存在

```c++
int ChildCount_CS(CSTree T, TElemType_CS p)
{
	int i, j, count;
	CSTree Q[100];
	
	count = -1;
	i = j = 0;
	
	if(T)
	{
		Q[j++] = T;
		
		while(i<j)
		{
			while(Q[i] && Q[i]->data!=p)
			{
				if(Q[i]->firstchild)
					Q[j++] = Q[i]->firstchild;
				
				Q[i] = Q[i]->nextsibling;
			}
			
			if(Q[i] && Q[i]->data==p)
				break;
				
			i++;
		}
		
		if(i<j)								//找到了p
		{
			count = 0;
			if(Q[i]->firstchild)
			{
				Q[i] = Q[i]->firstchild;
				while(Q[i])
				{
					count++;
					Q[i] = Q[i]->nextsibling;
				}
			}
		} 
	}
	
	return count;
}
```



### 返回树T中结点e的第i个孩子（层序计数）的指针

```c++
CSTree ChildSeat_CS(CSTree T, TElemType_CS e, int i)
{
	TElemType_CS tmp;
	CSTree p;
	
	tmp = ChildValue_CS(T, e, i);
	
	if(tmp)								//可以找到e的第i个孩子
		p = Order_CS(T, tmp);
	
	return p;
} 
```



### 将树t插入为树T中e结点的第i棵子树（层序计数），i=0定义为最后一棵子树

```c++
Status InsertTree_CS(CSTree T, TElemType_CS e, int i, CSTree t)
{
	int j, k0;
	CSTree p, q;
	
	k0 = ChildCount_CS(T, e);
	
	if(k0<0 || i<0 || i>k0+1)
		return ERROR;
	
	if(i==0)
		j = k0+1;
	else
		j = i;
	
	if(j==1)
	{
		p = Order_CS(T, e);
		t->nextsibling = p->firstchild;
		p->firstchild = t;
	}
	else
	{
		q = ChildSeat_CS(T, e, j-1);
		t->nextsibling = q->nextsibling;
		q->nextsibling = t;
	}
	
	return OK;
}
```



### 删除树T中e结点的第i棵子树

```c++
Status DeleteTree_CS(CSTree T, TElemType_CS e, int i)
{
	TElemType_CS tmp;
	CSTree p, q;
	
	if(i==1)
	{
		p = Order_CS(T, e);
		if(!p)
			return ERROR;
		q = p->firstchild->nextsibling;
		p->firstchild->nextsibling = NULL;
		ClearTree_CS(&(p->firstchild));
		p->firstchild = q;
	}
	else
	{
		p = ChildSeat_CS(T, e, i-1);
		if(!p)
			return ERROR;
		q = p->nextsibling->nextsibling;
		p->nextsibling->nextsibling = NULL;
		ClearTree_CS(&(p->nextsibling));
		p->nextsibling = q;
	}	
	
	return OK;
}
```



### 层序遍历树

```c++
void LevelOrderTraverse_CS(CSTree T, void(Visit)(TElemType_CS))
{
	int i, j;
	CSTree Q[100];
	
	i = j = 0;
	
	if(T)
		Q[j++] = T;
	
	while(i<j)
	{
		while(Q[i])
		{
			Visit(Q[i]->data);
		
			if(Q[i]->firstchild)
				Q[j++] = Q[i]->firstchild;
			
			Q[i] = Q[i]->nextsibling;
		}
		
		i++;
	}	
}
```



### 前序遍历树

```c++
void PreOrderTraverse_CS(CSTree T, void(Visit)(TElemType_CS))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse_CS(T->firstchild, Visit);
		PreOrderTraverse_CS(T->nextsibling, Visit);
	}
}
```



### 中序遍历树

```c++
void InOrderTraverse_CS(CSTree T, void(Visit)(TElemType_CS))
{
	if(T)
	{
		InOrderTraverse_CS(T->firstchild, Visit);
		Visit(T->data);
		InOrderTraverse_CS(T->nextsibling, Visit);
	}
}
```



### 按树的结构打印树

```c++
void Print_CS(CSTree T)
{
	typedef struct
	{
		TElemType_CS e;
		int x;
		int y;	
	}Node;
	
	SqStack S;
	SElemType_Sq tmp;
	Node node[100];
	int row, col, row_max, k, i, j;
	char a[100][100] = {};
	int m, n;
	
	k = 0;	
		
	if(T)
	{
		InitStack_Sq(&S);
		Push_Sq(&S, T);
		
		row = col = 0;
		row_max = 0;
		
		while(!StackEmpty_Sq(S))
		{
			GetTop_Sq(S, &tmp);
			
			node[k].e = tmp->data;
			node[k].x = col;
			node[k].y = row;
			k++;
			
			while(tmp->firstchild)
			{
				Push_Sq(&S, tmp->firstchild);
				row++;
				if(row_max<row)
					row_max = row;
				GetTop_Sq(S, &tmp);
				
				node[k].e = tmp->data;
				node[k].x = col;
				node[k].y = row;
				k++;		
			}
			
			Pop_Sq(&S, &tmp);
						
			if(tmp->nextsibling)
			{
				Push_Sq(&S, tmp->nextsibling);
				col++;		
			}
			else
			{
				while(!StackEmpty_Sq(S))
				{
					Pop_Sq(&S, &tmp);
					row--;
														
					if(tmp->nextsibling)
					{
						Push_Sq(&S, tmp->nextsibling);
						col++;
						break;
					}				
				}
			}
		}
	
		for(i=0; i<k; i++)
			a[node[i].x][3*node[i].y] = node[i].e;
		
		for(i=0; i<=col; i++)
		{
			for(j=0; j<=3*row_max; j++)
			{
				if(a[i][j])
					printf("%c", a[i][j]);
				else
					printf(".");
			}
		
			printf("\n");
		}			
	}
	else
		printf("空树无法打印！！\n");
}
```































































































# 第四章	数据结构算法描述



## 栈

### 中缀表达式转换成后缀表达式（逆波兰式），并对逆波兰表达式求值

> [Question-3.21-main.c](E:\数据结构和算法\数据结构严蔚敏\Data-Structure-master\▼配套习题解析\▼03 栈和队列\▼习题测试文档-03\Question-3.21-main.c)

> [Question-3.22-main.c](E:\数据结构和算法\数据结构严蔚敏\Data-Structure-master\▼配套习题解析\▼03 栈和队列\▼习题测试文档-03\Question-3.22-main.c)

