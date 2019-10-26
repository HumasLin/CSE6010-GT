/*
 * queue.h
 * For assignment 4
 * Created by Haomin Lin on 9/22/19.
 * Modified for Assignment 5 and finished on 10/08/19
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */


#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>

/*
* define the structure of a node in a priority queue
* the node includes data and attribute as the distance and label of a trainer
* using a pointer to connect to the next node
*/
typedef struct create_node {
    int sourceid;
    double weight;
    int parent;
    struct create_node *next;
}Node;

/*
 * define the structure of a priority queue
 * using a pointer to connect to nodes
 */
typedef struct create_queue {
    int sourceid;
    double degree;
    struct create_node *next;
}Queue;

/*
 * declaration of the function that creates a priority queue to store distances
 * this function create a priority queue with undecided size
 * it returns a pointer to this priority queue
 * it returns NULL when error
 */
Queue* create_queue(int source, double degree);


/*
 * declaration of the function that inserts a node according to its priority
 * q provided inside the function, data and attribute from arrays storing read data
 * this function gives node with smaller distance higher priority
 * it inserts nodes according to the priority
 * if the queue is empty, it simply inserts it
 * it returns 1 when successful while 0 when error
 */
int queue_insert(Queue *q, int sid, double weight, int parent);


/*
 * declaration of the function that prints the information of the node
 * q provided inside the function
 * it prints nodes with smallest distance coming out first
 * it prints specific message when priority queue is empty
 */
void print_queue(Queue *q);

/*
 * declaration of the function that stores and prints the longest path from current source node
 * q and source provided inside the function
 * it prints nodes with smallest distance coming out first
 * it prints specific message when priority queue is empty
 */
void print_path(Queue *q, int source);

/*
 * declaration of the function that releases all memory used by the contents of
 * priority queue
 * q provided inside the function
 * it frees the memory used by the contents of priority queue by freeing
 * nodes one by one
 */
void queue_free(Queue *q);

/*
 * declaration of the function that removes the node with longest distance
 * q provided inside the function, it removes the data just done calculating
 * it returns a pointer to the label of data deleted
 */
int remove_top_queue(Queue *q);

#endif /* queue_h */
