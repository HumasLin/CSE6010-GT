/*
 * KNN.hh
 * For assignment 4
 * Created by Haomin Lin on 9/22/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#ifndef KNN_h
#define KNN_h

#include "queue.h"/* include this .h file to use the structure in this file */
#include <stdio.h>

int *info;
int *sum; /* define an array to store clustering results for different dimensions */

/*
 * declaration of the function that
 * calculates and store the distances and labels of data
 * queue distances provided inside the function
 * size, dimension read from input files
 * r from the loop in the main function
 * it produces a priority queue with calculated results
 */
void all_distances(int size, int dimension, int r, Queue *distances);

/*
* declaration of the function that counts the nearest neighbors in each cluster
* queue distances provided inside the function
* k from input, attribute read from input files
* it produces an array storing information about number of nearest neighbors in
* a cluster
*/
void count_neighbors(int attribute, Queue* distances, int k);

/*
 * declaration of the function that labels the data to the nearest cluster
 * raw_size, attribute, dimension read from input files
 * r from the loop in the main function
 * it gives the label to the array that contains raw data
 */
void label_node(int raw_size, int attribute, int dimension, int r);

/*
 * declaration of the function that reads the raw data
 * filename from input
 * it produces a two dimensions array storing data read from input raw data file
 * it returns the number of raw data
 */
void read_raw_data(char* file_name);

/*
 * declaration of the function that reads the trainer data
 * filename from input
 * it produces a two dimensions array storing data read from input trainer data file
 * it returns the number of labels of trainer data
 */
void read_trainer_data(char* file_name);

/*
* declaration of the function that writes the results into the output file
* filename from input
* raw_size, dimension read from input files
* it writes the results into the output file
*/
void write_data(int raw_size, int dimension, char *outfile);

/*
 * declaration of the function that frees the arrays defined to store data
 * it frees 4 arrays
 */
void free_arrays(void);

#endif /* KNN_h */
