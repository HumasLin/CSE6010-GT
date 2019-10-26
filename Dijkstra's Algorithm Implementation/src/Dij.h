/*
 * Dij.h
 * For assignment 5
 * Created by Haomin Lin on 10/03/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#ifndef KNN_h
#define KNN_h

/*
* include queue.h to use the structure in this file
* this file is modified from the file created for Assignment 2
*/
#include "queue.h"
#include <stdio.h>

Queue** graph; /* define an array to store graph information */
Queue** result; /* define an array to store unvisited nodes in a round of graph analysis */
Queue** paths; /* define an array to store longest path for a source node */

double *distances; /* define an array to store distances from the source node to all other nodes */
int* visit; /* define an array to mark whether a node is visited */

int info; /* define a global variable as the number of nodes in the graph */
double maxi; /* define a global variable as the temporary distance of nodes in the graph */

/*
 * declaration of the function that reads the source data
 * filename from input
 * it produces a two dimensions array storing priority queues that stores data read from input source data file
 * it defines global varaiable info as the number of nodes in the graph
 */
void read_source_data(char* file_name);

/*
 * declaration of the function that relaxes all the nodes in the graph
 * n from the loop in the main function
 * it produces an array storing original distances of all the nodes but the source to the source
 */
void relax_all(int n);

/*
 * declaration of the function that initialize priority queues that stores all the nodes' current distance to the source
 * it prepares an a two dimensions array storing priority queues that are to store all the nodes' current distance to the source
 */
void result_init(void);

/*
 * declaration of the function that initializes the visit status of each node
 * it produces an array storing the visit status of each node with original value 0 as not visited
 */
void visit_init(void);

/*
 * declaration of the function that relaxes all the nodes in the graph
 * n from the loop in the main function
 * it calculates all other nodes' distances in the graph to the source
 * it runs funciton print_the_longest so prints and stores the longest distance from current source to other nodes
 */
void cal_distance(int n);

/*
 * declaration of the function that prints and stores the longest distance from current source to other nodes
 * n from the loop in the main function
 * it compares to get the farthest node
 * then it creates a priority queue with the longest path from the source, and prints and stores it in the array paths
 */
void print_the_longest(int n);

/*
 * declaration of the function that prints and stores the longest distance from current source to other nodes
 * value from the distance stored in array result
 * it updates the largest distance from the source to other nodes in the graph
 */
void store_the_max(double value);

/*
* declaration of the function that writes the results into the output file
* filename from input situation
* it writes the results into the output file
*/
void write_data(char* file_name);

#endif /* KNN_h */
