#include<stdio.h>
#include <stdlib.h>  // This is where malloc is declared

typedef struct list_t list; // Forward declaration with typedef

struct list_t
{
    int n;
    list *next; // 'list' is now valid as a typedef alias for 'struct list_t'
};

list *listPtr = NULL;

static list* createNode(void)
{
    list *newItem;
    newItem = (list*)malloc(sizeof(list));
    printf("Enter the item value\n\r");
    scanf("%d", &newItem->n);
    return(newItem);
};

void instertAtEnd()
{
    list *temp, *start;
    temp = createNode();
    /* Inserted node should point to NULL as its inserted at end */
    temp->next = NULL;

    if(listPtr == NULL)
    {
        listPtr = temp;
    }
    else
    {
        start = listPtr;
        while(start->next != NULL)
        {
            start = start->next;
        }
        start->next = temp;
    }
}
void display (void)
{
    if(listPtr == NULL)
    {
        printf("List is empty, cannot delete\n\r");
    }
    else
    {
      list *start = listPtr;
      printf("The list is\n\r");
      while(start != NULL) // it should not be start->next, it will not print the last node
      {
        printf("%d \n\r",start->n);
        start = start->next;
      }
    }
}
void deleteFromStart(void)
{
  if(listPtr == NULL)
  {
      printf("List is empty, cannot delete\n\r");
  }
  else
  {
      list *start = listPtr;
      /* If only one node is there in the list */
      if(listPtr->next == NULL)
      {
          listPtr = NULL;
          free(start);
      }
      else
      {
          listPtr = listPtr->next;
          free(start);
      }
      printf("Deleted node\n\r");
  }
}
void deleteFromEnd(void)
{
  if(listPtr == NULL)
  {
    printf("List is empty, cannot delete\n\r");
  }
  else
  {
      list *start = listPtr;
      /* If only one node is there in the list */
      if(listPtr->next == NULL)
      {
          listPtr = NULL;
          free(start);
      }
      else
      {
          while((start->next != NULL) && (start->next->next != NULL))
          {
              start = start->next;
          }
          free(start->next);
          start->next = NULL;
      }
      printf("Deleted node\n\r");
  }
}
int main()
{
    int n ;
    while(1)
    {
        printf("Enter 1 to insert node at end\n\rEnter 2 to display list\n\rEnter 3 to Delete from End\n\rEnter 4 to Delete from Start\n\rEnter 5 to exit\n\r");
        scanf("%d", &n);
        if(n == 1)
        {
           instertAtEnd();
        }
        else if(n == 2)
        {
           display();
        }
       else if(n == 3)
       {
           deleteFromEnd();
       }
       else if(n == 4)
       {
           deleteFromStart();
       }
       else
       {
           break;
       }
    }

    return 0;
}
