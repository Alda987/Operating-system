#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;   // next index to produce
int out = 0;  // next index to consume
int count = 0; // number of items in buffer

/* Producer function */
void producer(int id, int item)
{
    if(count == BUFFER_SIZE)
    {
        printf("Buffer full! Producer %d cannot produce item %d\n", id, item);
    }
    else
    {
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer %d produced item %d\n", id, item);
    }
}

/* Consumer function */
void consumer(int id)
{
    if(count == 0)
    {
        printf("Buffer empty! Consumer %d cannot consume\n", id);
    }
    else
    {
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer %d consumed item %d\n", id, item);
    }
}

int main()
{
    // Simulate producer-consumer sequence
    producer(1, 101);
    producer(2, 102);
    producer(1, 103);
    consumer(1);
    consumer(2);
    producer(2, 104);
    producer(1, 105);
    producer(2, 106);  // buffer full simulation
    consumer(1);
    consumer(2);
    consumer(1);
    consumer(2);
    consumer(1);       // buffer empty simulation

    return 0;
}
