/*
 * queue.c
 * For assignment 4
 * Created by Haomin Lin on 9/22/19. 
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * define function create_queue
 */
Queue* create_queue(){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if(q == NULL) {
        printf("Fatal Error: out of memory");
        return NULL;
    }
    else{
        q->next = NULL;
        return q;
    }
}

/*
 * define function queue_insert
 */
int queue_insert(Queue *q, double data, int attr){
    
    /* allocate memory for the inserted node */
    Node *node = (Node *)malloc(sizeof(Node));
    
    /* return 0 if allocation fails */
    if(node == NULL) {
        printf("Fatal Error: out of memory.\n");
        return 1;
    }
    node->data = data; /* assign data as the priority of inserted node */
    node->attr = attr; /* assign attribute as the label of the data */
    node->next = NULL;
    if(q->next == NULL) {
        q->next = node;
        return 0; /* directly insert data if it's the first */
    }
    else {
        Node *prev, *after;
        if(q->next->data >= data){
            prev = q->next; /* pointer to node after head moves forward */
            q->next = node; /* assign inserted node after head */
            node->next = prev; /* make inserted node connected with its next node */
            return 1;
        }
        /* insert the node according to its priority */
        else{
            prev = q->next; /* initialize the pointer to head */
            after = q->next->next; /* initialize the pointer to node after head */
            
            while(after != NULL && after->data < data){

                after = after->next;
                prev = prev->next; /* find its position according to the distance */
                    
            }
            prev->next = node; /* assign the pointer to inserted node */
            node->next = after; /* assign the pointer to the address after inserted node */
            return 1;
        }
    }
    return 0;
}

/*
 * define function print_queue
 */
void print_queue(Queue *q){
    /* report an empty queue with specific message */
    if(q->next == NULL){
        printf("You are printing an empty queue!\n");
    }
    /* print the priority queue with smallest distance first */
    else{
        for(Node *cur = q->next; cur != NULL; cur = cur->next) {
            /* print out the distances and label of the data */
            printf("%lf : %d\n", cur->data, cur->attr);
        }
    }
}
    

/*
 * define function remove_queue
 */
void remove_queue(Queue *q) {
    
    /* report error message when the queue is empty */
    if(q == NULL || q->next == NULL) {
        printf("Fatal error: there is no item in the queue.\n");
    }
    
    Node *node = q->next;
    q->next = q->next->next; /* connect queue to the next data in the queue */

    free(node); /* free the memory taken by deleted item */
}

/*
 * define function queue_free
 */
void queue_free(Queue *q){
    if(q == NULL){
        return;
    }
    Node *p; /* declare a pointer to save the temporary address of node to be deleted */
 
    /* keep deleting nodes when the priority is not empty */
    while(q->next)
    {
        p = q->next; /* assign the pointer to the node to be deleted */
        q->next = p->next; /* connect the head with nodes after the one to be deleted */
        free(p); /* free the node to be deleted */
    }
    free(q); /* free the head */
}

