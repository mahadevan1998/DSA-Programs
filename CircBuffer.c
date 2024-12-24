#include <stdio.h>
#include <stdbool.h>  // Include for bool, true, false

#define BUFFER_SIZE (10u)

typedef struct
{
    int buffer[10];
    int head;
    int tail;
    int size;
}CircularBuffer_Type;

void BufferInit(CircularBuffer_Type * CBuffPtr)
{
    CBuffPtr->head = 0;
    CBuffPtr->tail = 0;
    CBuffPtr->size = 0;
}
bool IsBufferFull(CircularBuffer_Type * CBuffPtr)
{
    return (CBuffPtr->size == BUFFER_SIZE);
}

bool IsBufferEmpty(CircularBuffer_Type * CBuffPtr)
{
  return (CBuffPtr->size == 0);
}

void Enqueue(CircularBuffer_Type * CBuffPtr, int data)
{
    if(IsBufferFull(CBuffPtr) == true)
    {
        printf("Buffer is Full\n\r");
    }
    else
    {
        CBuffPtr->buffer[CBuffPtr->tail] = data;
        CBuffPtr->tail = (CBuffPtr->tail + 1) % BUFFER_SIZE;
        CBuffPtr->size++;
    }
}

void Dequeue(CircularBuffer_Type * CBuffPtr, int *dataPtr)
{
    if(IsBufferEmpty(CBuffPtr) == true)
    {
        printf("Buffer is Empty\n\r");
    }
    else
    {
        *dataPtr = CBuffPtr->buffer[CBuffPtr->head];
        CBuffPtr->head = (CBuffPtr->head + 1) % BUFFER_SIZE;
        CBuffPtr->size--;
    }
}

void Peek(CircularBuffer_Type * CBuffPtr)
{
    if(IsBufferEmpty(CBuffPtr) == true)
    {
        printf("Buffer is Empty\n\r");
    }
    else
    {
        printf("The data at head is %d \n\r",CBuffPtr->buffer[CBuffPtr->head]);
    }
}
void Display(CircularBuffer_Type * CBuffPtr)
{
    int i;
    if(CBuffPtr->size == 0)
    {
        printf("Buffer is Empty\n\r");
    }
    for (i = 0; i < CBuffPtr->size; i++)
    {
        printf("%d\n\r", CBuffPtr->buffer[(CBuffPtr->head + i) % BUFFER_SIZE]);
    }
}
int main(void)
{
    int n ;
    int writeData;
    int readData;
    CircularBuffer_Type Buffer;
    BufferInit(&Buffer);
    while(1)
    {
        printf("Enter 1 to Enqueue at end\n\rEnter 2 to Dequeue\n\rEnter 3 to Peek\n\rEnter 4 to Display buffer\n\rEnter 5 to exit\n\r");
        scanf("%d", &n);
        if(n == 1)
        {
           printf("Enter data to enqueue\n\r");
           scanf("%d\n\r", &writeData);
           Enqueue(&Buffer, writeData);
        }
        else if(n == 2)
        {
           Dequeue(&Buffer, &readData);
           printf("The data read is %d\n\r", readData);
        }
        else if(n == 3)
        {
           Peek(&Buffer);
        }
        else if(n == 4)
        {
           Display(&Buffer);
        }
        else
        {
           break;
        }
    }

    return 0;
}
