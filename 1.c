#include<stdio.h>
#include <stdlib.h>
typedef struct Node{
    int coef;
    int exp;
    struct Node *next;
}Node;

typedef Node *List;

List createnode(int coef,int exp)
{
    List L = (List)malloc(sizeof(struct Node));
    L->coef =coef;
    L->exp =exp;
    L->next =NULL;
    return L;
}

List inputnode()
{
    int a=0;
    int b=0;
    List head=NULL;
    List last=NULL;
    while(1)
        {
            scanf("%d %d",&a,&b);
            if(a==0&&b==0){
                break;
            }
            List L;
            L=createnode(a,b);
            if(head==NULL)
                {
                    head=last=L;
                }
            else
                {
                    last->next = L;
                    last=L;
                }
        }
    return head;
}

void insertnode(List *head, int coef, int exp) {
    List L = createnode(coef, exp);
    if (*head == NULL || (*head)->exp < exp) {
        L->next = *head;
        *head = L;
    } else {
        List current = *head;
        while (current->next != NULL && current->next->exp > exp) {
            current = current->next;
        }
        if (current->next != NULL && current->next->exp == exp) {
            current->next->coef += coef;
            free(L);
        } else {
            L->next = current->next;
            current->next = L;
        }
    }
}

List add(List L1,List L2)
{
    List result =NULL;
    while(L1!=NULL&&L2!=NULL)
        {
            if(L1->exp>L2->exp)
                {
                    insertnode(&result,L1->coef,L1->exp);
                    L1 = L1->next;
                }
            else if(L1->exp == L2->exp)
                {
                    insertnode(&result,(L1->coef+L2->coef),L1->exp);
                    L1 = L1->next;
                    L2 = L2->next;
                }
            else
                {
                    insertnode(&result,L2->coef,L2->exp);
                    L2 = L2->next;
                }
        }
    while(L1!=NULL)
        {
            insertnode(&result,L1->coef,L1->exp);
            L1 = L1->next;
        }
    while(L2!=NULL)
        {
            insertnode(&result,L2->coef,L2->exp);
            L2 = L2->next;
        }
    return result;
}

void output(List L) {
    if (L == NULL) {
        printf("0");
        return;
    }
    int first = 1;
    while (L != NULL) {
        if (L->coef != 0) {
            if (!first && L->coef > 0) {
                printf("+");
            }
            if (L->exp == 0) {
                printf("%d", L->coef);
            } else if (L->exp == 1) {
                if (L->coef == 1) {
                    printf("x");
                } else if (L->coef == -1) {
                    printf("-x");
                } else {
                    printf("%dx", L->coef);
                }
            } else {
                if (L->coef == 1) {
                    printf("x^%d", L->exp);
                } else if (L->coef == -1) {
                    printf("-x^%d", L->exp);
                } else {
                    printf("%dx^%d", L->coef, L->exp);
                }
            }
            first = 0;
        }
        L = L->next;
    }
}

int main()
{
    List L1,L2,result;
    L1=inputnode();
    char op;
    if (scanf(" %c", &op) != 1 || op != '+')
        {
            output(L1);
        }
    else
        {
            L2 = inputnode();
            result = add(L1, L2);
            output(result);
        }
    return 0;
}
so it's a question to change the code that has existed
