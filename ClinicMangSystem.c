#include <stdio.h>
#include <stdlib.h>
#define SIZE 30
typedef struct node					//Pateint data
{
    char name[SIZE];
    char gender[SIZE];
    int age;
    int ID;
	int res;
    struct node* next;
} node;

void delete_node(struct node **start,int ID,struct node  **end);
void addnew (struct node **start,struct node **end,struct node** newpt) ;
void editPat(struct node *start);
void printPat (struct node *start,int num);
void reserveASlot (struct node *ptr,struct node *start);
void print(struct node *start);
void reservation (struct node *start);
struct node *createNode (struct node *start);
struct node *appendNode(struct node *end,struct node *newpt);
struct node *searchList(struct node *start,int data);
int searchID(struct node *start,int data);

int main (void)
{
    char choice =0 ;					//choosing user or admin modes
    char t=0;							//Trials
    int pass;							//Password
    int num;							//Patient ID variable
    int choice2;						//choosing feature
    struct node *start = NULL;
    struct node *end =   NULL;
    struct node *newpt = NULL;
	struct node *ptr =   NULL;
    while(choice != 'N' || choice != 'n')
    {
        if(t==3)
        {
            break;
        }
        printf("Do you want to continue in Admin mode or User mode \n");
        printf("'A' for Admin mode or 'U' for User modes or 'N' to exit : ");
        scanf("\n%c",&choice);
        if(choice == 'A' || choice == 'a')
        {
            if(t<3)
            {
                pass = 0;
            }
            else
            {
                //Nothing
            }
            while(t<3 && pass != 1234)
            {
                printf("Enter the password : ");
                scanf("%d",&pass);
                if(pass == 1234)
                {
                    printf("------------------------------------------------Admin Mode------------------------------------------------ \n");
                    while(1)
                    {
                        printf("If you want to add a new patient enter '1'\n");
                        printf("If you want to edit a patient recored enter '2'\n");
                        printf("If you want to exit Admin mode enter '3'\n");
                        printf("If you want to cancle a reservation enter '4'\n");
						printf("If you want to reserve a slot with the doctor type '5'\n");
                        scanf("%d",&choice2);
                        if(choice2==1)
                        {
                            addnew(&start,&end,&newpt);
                        }
                        else if(choice2==3)
                        {
                            break;
                        }
                        else if(choice2==2)
                        {
                            editPat(start);
                        }
                        else if(choice2 ==4)
                        {
                            printf("Enter the ID : ");
                            scanf("%d",&num);
                            delete_node(&start,num,&end);
                        }
						else if(choice2 ==5)
						{
							printf("Enter the ID: ");
							scanf("%d",&num);
							ptr = searchList(start,num);
							reserveASlot(ptr,start);
						}
                        else
                        {
                            printf("Worng Input!\n");
                        }
                    }
                }
                else
                {
                    t++;
                }
            }
        }
        else if (choice == 'U' || choice =='u')
        {
			printf("------------------------------------------------User Mode------------------------------------------------ \n");
			while(1)
			{
				choice2=0;
				printf("For viewing Pateint record enter '1'\n");
				printf("Print Reservations enter  '2'\n");
				printf("To exit user mode enter '3'\n");
				printf("To print all Patient data enter '4'\n");
				scanf("%d",&choice2);
				if(choice2 ==1)
				{
					printf("Enter Pateint ID : ");
					scanf("%d",&num);
					printPat(start,num);
					printf("------------------------------------------------\n");
				}
				else if(choice2 == 2)
				{
					printf("List  : \n");
					reservation(start);
				}
				else if(choice2 == 3)
				{
					break;
				}
				else if(choice2 == 4)
				{
					print(start);
				}
				else 
				{
					printf("Wrong Input !\n");
				}
			}
		}
		else if(choice == 'N' || choice == 'n')
		{
			break;
		}
        else
        {
            printf("Wrong Input!!\n");
        }
    }
    return 0;
}
void addnew (struct node **start,struct node **end,struct node** newpt)
{
    if(*start == NULL)
    {
        *start = createNode(*start);
        *end = *start;
    }
    else
    {
        *newpt = createNode(*start);
        *end =  appendNode(*end,*newpt);
    }
	printf("Done!\n");
}
struct node *createNode (struct node *start)
{
    struct node *ptr;
    ptr = (struct node*) malloc(sizeof(struct node));
    printf("Enter Name : ");
    scanf("\n%[^\n]%*c",ptr->name);
    printf("Enter Gender : ");
    scanf("\n%[^\n]%*c",ptr->gender);
    printf("Enter age : ");
    scanf("%d",&ptr->age);
	ptr->next = NULL;
    while(1)
    {
        printf("Enter ID : ");
        scanf("%d",&ptr->ID);
        if(searchID(start,ptr->ID) == 0)
        {
            break;
        }
        else
        {
            printf("This ID is already existed.\n");
        }
    }
    return ptr;
}
struct node *appendNode(struct node *end,struct node *newpt)
{
    end->next = newpt;
    return newpt;
}
void printPat (struct node *start,int num)
{
    struct node *ptr;
    ptr = searchList(start,num);
    if(ptr != NULL)
    {
		printf("------------------------------------------------\n");
        printf("Name = %s\n",ptr->name);
        printf("Gender = %s\n",ptr->gender);
        printf("Age = %d\n",ptr->age);
    }
    else
    {
        printf("ID not Found.\n");
    }
}
int searchID(struct node *start,int data)
{
    int c=0;
    struct node *ptr = start;
    while(ptr != NULL)
    {
        if(ptr->ID == data)
        {
            c++;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return c;
}
struct node *searchList(struct node *start,int data)
{
    struct node *ptr = start;
    while(ptr != NULL)
    {
        if(ptr->ID == data)
        {
			return  ptr;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return ptr;
}
void editPat(struct node *start)
{
    int num;
    struct node *ptr =NULL;
    printf("Enter the ID you want to edit on : ");
    scanf("%d",&num);
    ptr = searchList(start,num);
    if(ptr == NULL)
    {
        printf("ID not Found\n");
    }
    else
    {
        printf("Enter Name : ");
        scanf("\n%[^\n]%*c",ptr->name);
        printf("Enter Gender : ");
        scanf("\n%[^\n]%*c",ptr->gender);
        printf("Enter age : ");
        scanf("%d",&ptr->age);
	}
}
void delete_node(struct node **start,int data,struct node **end)
{
    struct node *det = NULL;
    struct node *ptr = *start;
    while(ptr != NULL)
    {
		if(ptr->ID == data)
		{
			det = *start;
			*start = ptr->next;
			free(det);
			printf("Done!\n\n");
			break;
		}
        else if(ptr->next->ID == data)
        {
            if(ptr->next == *end)
            {
                det = *end;
                *end = ptr;
                ptr->next = NULL;
                free(det);
				printf("Done!\n\n");
                break;
            }
            else
            {
				det = ptr->next;
                ptr->next = ptr->next->next;
                free(det);
				printf("Done!\n\n");
                break;
            }
        }
        ptr = ptr->next;
    }
	if(ptr == NULL)
	{
		printf("ID not Found !\n");
	}		
}
int searchRES(struct node *start,int data)
{
	int c=0;
	struct node *ptr = start;
	while(ptr != NULL)
	{
		if(ptr->res == data)
		{
			c++;
			ptr = ptr->next;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return c;
}
void reservation (struct node *start)
{
	struct node *ptr = start ;
	while(ptr != NULL)
	{
		if(ptr->res == 1)
		{
			printf("ID %d have a reservation from 2 to 2:30 pm\n",ptr->ID);
		}
		else if(ptr->res == 2)
		{
			printf("ID %d have a reservation from 2:30 to 3 pm\n",ptr->ID);
		}
		else if(ptr->res == 3)
		{
			printf("ID %d have a reservation from 3 to 3:30 pm\n",ptr->ID);
		}
		else if(ptr->res == 4)
		{
			printf("ID %d have a reservation from 4 to 4:30 pm\n",ptr->ID);
		}
		else if(ptr->res == 5)
		{
			printf("ID %d have a reservation from 4:30 to 5 pm\n",ptr->ID);
		}
		ptr = ptr->next;
	}
	printf("\n\n");
}
void reserveASlot (struct node *ptr,struct node *start)
{
	int num;
	if(ptr == NULL)
	{
		printf("ID Not Found \n");
	}
	else 
	{
		while(1)
		{
			printf("Enter Reservation :\n");
			printf("(1) From 2pm to 2:30pm : \n");
			printf("(2) From 2:30pm to 3pm : \n");
			printf("(3) From 3pm to 3:30pm : \n");
			printf("(4) From 4pm to 4:30pm : \n");
			printf("(5) From 4:30pm to 5pm : \n");
			scanf("%d",&num);
			if((num >0) && (num <=5))
			{
				if(searchRES(start,num) == 0)
				{
					ptr->res = num;
					printf("Done!\n\n");
					break;
				}
				else
				{
					printf("This Reservation is already taken.\n");
				}	
			}
			else 
			{
				printf("This reservation is not valid \n");
			}
		}
	}
}
void print(struct node *start)
{
	struct node* ptr = start;
	while (ptr != NULL)
	{
		printPat(ptr,ptr->ID);
		ptr = ptr->next;
	}
	printf("------------------------------------------------\n");
}