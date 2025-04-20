#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 6
#define NAME_SIZE 50


char q[M][NAME_SIZE];  //Declaring a q
int front = -1, rear = -1;  //To store the parts using q

void enq(char* part)  //To add the parts 
{
    if (rear == M - 1) 
    {
        printf("Queue full!\n");  //Checking the full condition 
        return;
    }
    if (front == -1) front = 0;
    strcpy(q[++rear], part);
}

char* deq()  //To remove the parts 
{
    if (front == -1 || front > rear)
    {
        printf("Queue empty!\n");  //Checking the empty condition 
        return NULL;
    }
    return q[front++];
}


char stack[M][NAME_SIZE];     //Declaring a stack
int top = -1;//Stacking parts in LIFO order for load balancing

void push(char* part)   //To add the part to the top.
{
    if (top == M - 1) 
    {
        printf("Stack full!\n"); //Checking the full condition 
        return;
    }
    strcpy(stack[++top], part);
}

char* pop()   //To removes the top part (used for assembly order).
{
    if (top == -1) 
    {
        printf("Stack empty!\n");
        return NULL;
    }
    return stack[top--];
}
 
char storage[M][NAME_SIZE];//Using array to store cranes
int storageCount = 0;

void storeCrane(char* crane)  //To insert cranes
{

    if (storageCount < M)  
    {
        strcpy(storage[storageCount++], crane);
    } 
    else 
    {
        printf("Storage full. Deploying: %s\n", storage[0]);
        for (int i = 1; i < M; i++)
        {
            strcpy(storage[i - 1], storage[i]);
        }
        strcpy(storage[M - 1], crane);
    }
}

void displayStorage()  //To display the parts and cranes stored 
{
    printf("Current Storage:\n");
    for (int i = 0; i < storageCount; i++)
    {
        printf("%s ", storage[i]);
    }
    printf("\n");
}


typedef struct Node //Using structure of node 
{
    char crane[NAME_SIZE];
    struct Node* next;
} Node;

Node* faultyHead = NULL;

void insertFaulty(char* crane)//To adds faulty cranes to the front
{
    Node* temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->crane, crane);
    temp->next = faultyHead;
    faultyHead = temp;
}

void displayFaulty() //To display a crane which is faulty
{
    Node* temp = faultyHead;
    printf("Faulty Cranes: ");
    while (temp)
    {
        printf("%s ", temp->crane);
        temp = temp->next;
    }
    printf("\n");
}

void deleteFaulty(char* crane)//To remove a crane after it's repair
{
    Node *temp = faultyHead, *prev = NULL;
    while (temp != NULL && strcmp(temp->crane, crane) != 0) 
    {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev) faultyHead = temp->next;
    else prev->next = temp->next;
    free(temp);
}


typedef struct DNode //Using a doubly linked list
{
    char crane[NAME_SIZE];
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* repairedHead = NULL;  //Initialising the pointers
DNode* repairedTail = NULL;

void insertRepaired(char* crane)//To add repaired cranes to the end
{
    DNode* temp = (DNode*)malloc(sizeof(DNode));
    strcpy(temp->crane, crane);
    temp->prev = repairedTail;
    temp->next = NULL;
    if (repairedTail) repairedTail->next = temp;
    repairedTail = temp;
    if (!repairedHead) repairedHead = temp;
}

void traverseForward()
//To show repaired cranes from oldest to newest.
{
    DNode* temp = repairedHead;
    printf("Repaired (Forward): ");
    while (temp) 
    {
        printf("%s ", temp->crane);
        temp = temp->next;
    }
    printf("\n");
}

void traverseReverse()//To show the traverse list newest to oldest
{
    DNode* temp = repairedTail;
    printf("Repaired (Reverse): ");
    while (temp) 
    {
        printf("%s ", temp->crane);
        temp = temp->prev;
    }
    printf("\n");
}


typedef struct CNode 
{
    char crane[NAME_SIZE];
    struct CNode* next;
} CNode;

CNode* upgradeTail = NULL;

void insertUpgrade(char* crane) 
{
    CNode* temp = (CNode*)malloc(sizeof(CNode));
    strcpy(temp->crane, crane);
    if (!upgradeTail) 
    {
        temp->next = temp;
        upgradeTail = temp;
    } else 
    {
        temp->next = upgradeTail->next;
        upgradeTail->next = temp;
        upgradeTail = temp;
    }
}

void traverseCircular(int rounds) 
{
    if (!upgradeTail) return;
    CNode* temp = upgradeTail->next;
    printf("Priority Upgrades: ");
    for (int i = 0; i < rounds * 2; i++) 
    {
        printf("%s ", temp->crane);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int x; // x= choice chosen by user
    char input[NAME_SIZE];
    for(int i=1;i>0;i++)
    {
    printf("\n---- Crane Fabrication Unit ----\n");
    printf("1. Add Parts & Assemble Crane\n");
    printf("2. Store Crane in Yard\n");
    printf("3. Mark Crane as Faulty\n");
    printf("4. Repair a Faulty Crane\n");
    printf("5. Add Priority Upgrade\n");
    printf("6. View Storage, Faulty & Repaired Cranes\n");
    printf("7. Traverse Upgrade Cranes\n");
    printf("0. Exit\n");
    
     
        printf("Choose an option: ");
        scanf("%d", &x);
        getchar(); // consume newline

        switch (x) {
            case 1:
                printf("Enter parts (up to 6):\n");
                for (int i = 0; i < 6; i++) {
                    if (rear == M - 1) {
                        printf("Queue is full. Cannot add more parts.\n");
                        break;
                    }
                    printf("Part %d: ", i + 1);
                    fgets(input, NAME_SIZE, stdin);
                    input[strcspn(input, "\n")] = 0;
                    enq(input);
                }


                for (int i = 0; i < 6; i++) {
                    push(deq());
                }
                

                printf("Assembled Order (LIFO): ");
                for (int i = 0; i < 6; i++) {
                    printf("%s ", pop());
                }
                printf("\n");
                break;

            case 2:
                printf("Enter Crane Name to Store: ");
                fgets(input, NAME_SIZE, stdin);
                input[strcspn(input, "\n")] = 0;
                storeCrane(input);
                break;

            case 3:
                printf("Enter Faulty Crane Name: ");
                fgets(input, NAME_SIZE, stdin);
                input[strcspn(input, "\n")] = 0;
                insertFaulty(input);
                break;

            case 4:
                printf("Enter Crane Name to Repair: ");
                fgets(input, NAME_SIZE, stdin);
                input[strcspn(input, "\n")] = 0;
                deleteFaulty(input);
                insertRepaired(input);
                break;

            case 5:
                printf("Enter Crane Name for Priority Upgrade: ");
                fgets(input, NAME_SIZE, stdin);
                input[strcspn(input, "\n")] = 0;
                insertUpgrade(input);
                break;

            case 6:
                displayStorage();
                displayFaulty();
                traverseForward();
                traverseReverse();
                break;

            case 7:
                traverseCircular(2);
                break;

            case 0:
                printf("Exiting program.\n");
                exit(0);
                break;

            default:
                printf("Invalid option. Try again.\n");
        }

    }

    return 0;
}