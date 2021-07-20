#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node//Node of the BST
{
    char name[50];
    char number[15];
    int height;
    struct node* lchild;
    struct node* rchild;
};
struct hashNode{
    char name[50];
    char number[15];
    struct hashNode* next;
};
struct hashNode* hashMap[100000];
struct node* root;//Declaring global node
struct node* parent=NULL;//Declaring a global parent variable.
void init()
{
    int i;
    for(i = 0; i < 100000; i++)
        hashMap[i] = NULL;
}


struct node* rightRotate(struct node* y);
struct node* leftRotate(struct node* x);
struct node* addNode(char Name[],char Number[]);
struct node* findSuccessor(struct node* p);
int max(int a,int b);
int height(struct node *n);
int getBalance(struct node *n);
struct node* InsertNode(struct node* node,char Name[],char Number[]);
void displayDictionaryOrder(struct node* p);
struct node* searchByName(struct node*p,char Name[]);
struct node* deletion(struct node* node, char name[]);
int hashFunction(char number[]);
void insertHash(char name[], char number[]);
struct hashNode* searchByNumber(char number[]);
void deleteHash(char number[]);


int main()
{
    init();
    printf("\t\t\tWelcome to PhoneBook\n\n\n");
    for(;;)//Menu driven infinite loop
    {
        printf("Enter your choice from below:\n");//giving choices
        printf("1.Add new entry\n2.Remove entry\n3.Search entry\n4.List entries in dictionary order\n5.Exit\n");
        printf("Enter your choice: ");
        int choice;
        char c;
        scanf("%d%c",&choice,&c);
        system("clear");
        char Name[50],Number[15];
        int x;
        switch(choice)//executing the required choice
        {
            case 1:
                printf("Enter Name: ");
                scanf("%s",Name);
                printf("Enter Number: ");
                scanf("%s",Number);
                system("clear");
                root=InsertNode(root,Name,Number);
                insertHash(Name,Number);
                printf("Contact saved successfully.\n");
                getchar();
                break;
            case 2:
                printf("Enter Name to be deleted:");
                scanf("%s",Name);
                root=deletion(root,Name);
                struct node* rip=searchByName(root,Name);
                deleteHash(rip->number);
                printf("Deleted Successfully.\n");
                break;
            case 3:
                printf("Enter 1 to search by Name");
                printf(" and 2 to search by Number:");
                scanf("%d",&x);
                scanf("%c",&c);
                if(x==1){
                    printf("Enter the name: ");
                    scanf("%s",Name);
                    struct node* result=searchByName(root,Name);
                    printf("%s-%s\n",result->name,result->number);
                }
                else{
                    printf("Enter the number: ");
                    scanf("%s",Number);
                    struct hashNode* result=searchByNumber(Number);
                    printf("%s-%s\n",result->name,result->number);
                }
                getchar();
                break;
            case 4:
                if(root==NULL)
                    printf("Phone-Book is empty!!\n");
                else{
                    printf("The Entries in dictionary order are as follows:\n");
                    displayDictionaryOrder(root);
                }
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Enter valid choice!!\n");
        }
        getchar();
        system("clear");
    }
    return 0;
}
struct node* rightRotate(struct node* y){
    struct node* x=y->lchild;
    struct node* T2=x->rchild;

    y->lchild=T2;
    x->rchild=y;

    y->height=max(height(y->rchild),height(y->lchild))+1;
    x->height=max(height(x->rchild),height(x->lchild))+1;

    return x;
}
struct node* leftRotate(struct node* x){
    struct node *y = x->rchild;
    struct node *t2 = y->lchild;

    y->lchild = x;
    x->rchild = t2;

    x->height = max(height(x->lchild),height(x->rchild))+1;
    y->height = max(height(y->lchild),height(y->rchild))+1;

    return y;
}
struct node* addNode(char Name[],char Number[])//utility function to create and return a node
{
        struct node* y;
        y=(struct node*)malloc(sizeof(struct node));
        strcpy(y->name,Name);
        strcpy(y->number,Number);
        y->height=1;
        y->lchild=NULL;
        y->rchild=NULL;
        return y;
}
struct node* findSuccessor(struct node* p)//Finds and returns the successor in deletion process having both child present.
{
    while(p->lchild!=NULL)
    {
        parent=p;
        p=p->lchild;
    }
    return p;
}
int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
int height(struct node *n)
{
    if(n==NULL)
        return 0;
    return n->height;
}
int getBalance(struct node *n){
    if(n==NULL)
        return 0;
    return height(n->lchild)-height(n->rchild);
}
struct node* InsertNode(struct node* node,char Name[],char Number[])//function for inserting a node in tree
{
    int x=0;
    if(node==NULL)//enters the data to node node i.e. first node.
    {
        node=addNode(Name,Number);
        return node;
    }
    if(strcmp(Name,node->name)<0)
    {
        node->lchild=InsertNode(node->lchild,Name,Number);
    }
    else if(strcmp(Name,node->name)>0){
        node->rchild = InsertNode(node->rchild,Name,Number);
    }
    else
    {
        return node;
    }
    node->height=max(height(node->rchild),height(node->lchild))+1;
    int balance = getBalance(node);
    if(balance > 1 && strcmp(Name,node->lchild->name)<0)
    {
        return rightRotate(node);
    }
    if(balance < -1 && strcmp(Name,node->rchild->name)>0)
    {
        return leftRotate(node);
    }
    if(balance > 1 && strcmp(Name,node->lchild->name)>0){
        node->lchild = leftRotate(node->lchild);
        return rightRotate(node);
    }
    if(balance<-1 && strcmp(Name,node->rchild->name)>0)
    {
        node->rchild=rightRotate(node->rchild);
        return leftRotate(node->lchild);
    }
    return node;
}
void displayDictionaryOrder(struct node* p)//display in ascending order
{
    if(p!=NULL)
    {
        displayDictionaryOrder(p->lchild);
        printf("%-15s-%s\n",p->name,p->number);
        displayDictionaryOrder(p->rchild);
    }
}
struct node* searchByName(struct node*p,char Name[])//just a searching algorithm
{
    struct node* result;
    result=(struct node*)malloc(sizeof(struct node));
    strcpy(result->name,"The person doesn't exist in your ");
    strcpy(result->number,"list.");
    result->lchild=NULL;
    result->rchild=NULL;
    while(p!=NULL)
    {
        if(strcmp(p->name,Name)==0)
        {
            strcpy(result->name,p->name);
            strcpy(result->number,p->number);
            break;
        }
        if(strcmp(Name,p->name)<0)
        {
            p=p->lchild;
        }
        else if(strcmp(Name,p->name)>0){
            p=p->rchild;
        }
    }
    return result;
}
struct node* deletion(struct node* node, char name[]){
    if(node == NULL)
        return node;
    if(strcmp(name,node->name)<0)
    {
        node->lchild = deletion(node->lchild,name);
    }
    else if(strcmp(name,node->name)>0)
    {
        node->rchild = deletion(node->rchild,name);
    }
    else{
        if(node->rchild==NULL || node->lchild==NULL){
            struct node* temp=node->lchild?node->lchild:node->rchild;
            if(temp==NULL)
            {
                temp=node;
                node=NULL;
            }
            else
                *node = *temp;
                free(temp);
        }
        else{
            struct node* temp = findSuccessor(node->rchild);
            strcpy(node->name,temp->name);
            node->rchild = deletion(node->rchild,temp->name);
        }
    }
    if(node==NULL){
        return node;
    }
    node->height = 1 + max(height(node->lchild),height(node->rchild));
    int balance=getBalance(node);
    if(balance>1 && getBalance(node->lchild)>=0)
    {
        return rightRotate(node);
    }
    if(balance > 1 && getBalance(node->lchild)<0)
    {
        node->lchild=leftRotate(node->lchild);
        return rightRotate(node);
    }
    if(balance<-1 && getBalance(node->rchild)<=0)
    {
        return leftRotate(node);
    }
    if(balance<-1 && getBalance(node->rchild)>0)
    {
        node->rchild=rightRotate(node->rchild);
        return leftRotate(node);
    }
    return node;
}

int hashFunction(char number[]){
    long x = atol(number);
    int sum=0;
    long a = x;
    while(a>0){
        sum += a%10;
        a /= 10;
    }
    int key=1;
    for(int i=0;i<sum;i++)
    {
        key=(key*37)%100000;
    }
    return key;
}

void insertHash(char name[], char number[]){
    struct hashNode *newNode =(struct hashNode*) malloc(sizeof(struct hashNode));
    strcpy(newNode->name,name);
    strcpy(newNode->number,number);
    newNode->next=NULL;

    int key = hashFunction(number);
    if(hashMap[key]==NULL)
        hashMap[key]=newNode;
    else
    {
        struct hashNode *p = hashMap[key];
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=newNode;
    }
}

struct hashNode* searchByNumber(char number[]){
    int key = hashFunction(number);
    struct hashNode *p = hashMap[key];
    struct hashNode* ans;
    ans=(struct hashNode*)malloc(sizeof(struct hashNode));
    while (p!=NULL && strcmp(hashMap[key]->number,number)!=0)
    {
        p=p->next;
    }
    if(p==NULL)
    {
        strcpy(ans->name,"No such contact ");
        strcpy(ans->number,"exists");
        ans->next=NULL;
        return ans;
    }
    else{
        strcpy(ans->name,p->name);
        strcpy(ans->number,p->number);
        ans->next=NULL;
        return ans;
    }
}

void deleteHash(char number[]){
    /*int key = hashFunction(number);
    struct hashNode *p = hashMap[key];
    struct hashNode* q = p;
    if(strcmp(p->number,number)==0)
    {
        hashMap[key]=p->next;
        p->next=NULL;
        free(p);
        return;
    }
    while (p!=NULL && strcmp(p->number,number)!=0)
    {
        p=p->next;
        if(p!=NULL)
           q=p;
    }
    //struct hashNode* q=p->next;
    q->next=p->next;
    p->next=NULL;
    free(p);
    return;*/
    int key = hashFunction(number);
    struct hashNode *temp = hashMap[key], *dealloc;
    if(temp != NULL)
    {
        if(strcmp(temp->number,number)==0)
        {
            dealloc = temp;
            temp = temp->next;
            free(dealloc);
            return;
        }
        else
        {
            while(temp->next)
            {
                if(strcmp(temp->next->number,number))
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return;
                }
                temp = temp->next;
            }
        }
    }
}





