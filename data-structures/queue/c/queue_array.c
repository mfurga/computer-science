// Queue using the fixed-sized array.

#include <stdlib.h>
#include "queue_array.h"

queue_t *create_queue(int capacity)
{
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  if (queue == NULL)
    exit(EXIT_FAILURE);

  queue->capacity = capacity + 1;
  queue->read = 0;
  queue->write = 0;
  queue->array = (int *)malloc(sizeof(int) * queue->capacity);
  if (queue->array == NULL)
    exit(EXIT_FAILURE);

  return queue;
}

void enqueue(queue_t *queue, int value)
{
  if ((queue->write + 1) % queue->capacity == queue->read)
    return;  // The queue is full.

  queue->array[queue->write] = value;
  queue->write = (queue->write + 1) % queue->capacity;
}

int dequeue(queue_t *queue)
{
  if (queue->write == queue->read)
    return -1;  // The queue is empty.

  int res = queue->array[queue->read];
  queue->read = (queue->read + 1) % queue->capacity;
  return res;
}
