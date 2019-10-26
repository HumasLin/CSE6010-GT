/*
 * Dij.c
 * For assignment 5
 * Created by Haomin Lin on 10/03/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Dij.h"/* include Dij.h for functions in this file */
/*
* include queue.h to use the structure in this file
* this file is modified from the file created for Assignment 2
*/
#include "queue.h"

/*
 * define function read_source_data
 */
void read_source_data(char* file_name){
    
    /* declare variables for nodes, degreee of source node and weight of every edge */
    int num, linked;
    double degree, weight;
    
    FILE *fread = fopen(file_name, "r");
    
    /* report error if file opening fails */
    if(fread == NULL){
        printf("No data!\n");
        exit(0);
    }
    
    /*
     * read the number of nodes for later use
     */
    fscanf(fread, "%d", &info);
    
    /* allocate space for two dimension arrays */
    graph = (Queue**)malloc(info * sizeof(Queue));
    
    for(int k = 0; k < info; k++){
        /* read number and degree of the source node for late use */
        fscanf(fread, "%d %lf", &num, &degree);
        
        graph[k] = (Queue*)malloc(sizeof(Queue));
        
        /* prepare a priority queue to store information for each source node space */
        Queue* q = create_queue(num, degree);

        /* put the read data into the array */
        for(int n = 0; n < degree; n++){
            /* read the information of each node linked to the source */
            fscanf(fread, "%d %lf", &linked, &weight);
            
            /* put the read data into the priority queue and sort according to distance */
            queue_insert(q, linked, weight, num);
        }
        /* put the finished queue into the cell */
        graph[num] = q;
    }
}

/*
 * define function relax_all
 */
void relax_all(int n){
    /* initialize and allocate space for array distance */
    distances = (double*)malloc(info * sizeof(double));
    for(int i = 0; i < info ; i++){
        if(i == n){
            distances[i] = 0; /* mark the source node as no distance */
        }
        else{
            distances[i] = INFINITY; /* set other nodes with distance INFINITY */
        }
    }
}

/*
 * define function visit_int
 */
void visit_init(){
    /* initialize and allocate space for array distance */
    visit = (int*)malloc(info*sizeof(int));
    for(int i = 0; i < info ; i++){
        visit[i] = 0; /* set all the nodes as not visited */
    }
}

/*
 * define function result_init
 */
void result_init(){
    /* initialize and allocate space for two-dimensional array result */
    result = (Queue**)malloc((info)* sizeof(Queue*));
    for(int j = 0; j < (info); j++){
        /* prepare a priority queue to temporarily store information for each node */
        Queue *r = create_queue(j, 0);
        result[j] = (Queue*)malloc(sizeof(Queue));
        /* put the empty queue into the cell */
        result[j] = r;
    }
}

/*
 * define function cal_distance
 */
void cal_distance(int n){
    /* declare variables for the id of nodes in the graph and the number of visits */
    int no;
    int visit_time = 0;
    
    /* run the initialization functions to get prepared */
    visit_init();
    result_init();
    relax_all(n);
    
    /* create a priority queue to store the calculation results */
    Queue* S = create_queue(n, n);
    /* put the source node in queue S to start with */
    queue_insert(S, n, 0, 0);
    
    /* analyze the distances for every node to the source node*/
    while(S->next != NULL && visit_time != info){
        
        /* define the node being visted */
        int source_id = S->next->sourceid;
        
        /* define the node whose distance is to be calculated */
        Node* node = graph[source_id]->next;
        
        /* calculate all the nodes linked to the "source node" */
        while(node != NULL){
            
            /* skip the node that has been visited */
            if(visit[node->sourceid] == 1){
                node = node->next;
                continue;
            }
            else{
                int id = node->sourceid;
                
                /* relax the node if needed and then update its distance from source to itself */
                if(node->weight + distances[source_id] <= distances[id])
                {
                    distances[id] = node->weight + distances[source_id];
                    queue_insert(S, id, distances[id], source_id);
                    queue_insert(result[id], id, distances[id], source_id);
                }
                node = node->next;
            }
        }
        no = remove_top_queue(S); /* remove the visited node */
        /*mark the visited node*/
        if(visit[no] != 1){
            visit[no] = 1; /* mark the node as visited */
            visit_time++; /* log the visit */
        }
    }
    
    /* free queue S to clean redundant results */
    queue_free(S);
    
    /* run the function to print out and store the longest path for node i */
    print_the_longest(n);
}

/*
 * define function store_the_max
 */
void store_the_max(double value){
    
    /* update the max distance from the source to other nodes */
    if(value > maxi){
        maxi = value;
    }
}

/*
 * define function print_the_longest
 */
void print_the_longest(int n){
    
    /* initialize variables for later use*/
    double max_d = 0;
    int max_no = 0;
    int parent_to = 0;
    
    /* allocate space for a priority queue */
    paths[n] = (Queue*)malloc(sizeof(Queue));
    
    /* sort out the farthest node from the source node */
    for(int i = 0; i < info; i++){
        if (distances[i] > max_d){
            max_d = distances[i];
            max_no = i;
        }
    }
    
    /* run the function store_the_max to update max distance if needed */
    store_the_max(max_d);
    
    /* create a priority queue to store nodes on the path */
    Queue* p = create_queue(max_no, max_d);
    
    /* put the queue into the cell */
    paths[n] = p;
    
    /* initialize a starting node and get its parent */
    Node* cur = result[max_no]->next;
    parent_to = cur->parent;
    
    /* track the path using the parent id */
    while(parent_to != n){
        queue_insert(paths[n], max_no, 0, parent_to);
        parent_to = result[parent_to]->next->parent;
    }
    
    /* print out the path */
    printf("Path for %d:\n", n);
    print_path(paths[n], n);
}

/*
 * define function write_data
 */
void write_data(char* file_name){
    
    FILE* fwrite = fopen(file_name, "w");
    
    /* report error if file creation fails */
    if (fwrite == NULL){
        printf("Failed!");
    }
    
    /* write the max distance as diameter into output files */
    fprintf(fwrite, "The diameter is: %lf\n", maxi);
    
    /* write each path into output files */
    for(int i = 0; i < info; i++){
        fprintf(fwrite, "Node #%d:\n", i);
        fprintf(fwrite, "The Longest distance of it:");
        fprintf(fwrite, "%lf\n", paths[i]->degree);
        fprintf(fwrite, "The Longest path of it:");
        fprintf(fwrite, "%d->", i);
        for(Node* typer = paths[i]->next;typer != NULL; typer = typer->next){
            if(typer->next != NULL){
                fprintf(fwrite, "%d->", typer->parent);
            }
            else{
                fprintf(fwrite, "%d", typer->parent);
            }
        }
        
        /* write the farthest node id */
        if(paths[i]->next == NULL){
             fprintf(fwrite, "%d", paths[i]->sourceid);
        }
        else{
             fprintf(fwrite, "->%d", paths[i]->sourceid);
        }
        fprintf(fwrite, "\n");
    }
    fclose(fwrite);
}
