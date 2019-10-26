/*
 * main.c
 * For assignment 4
 * Created by Haomin Lin on 9/22/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "KNN.h" /* include two .h files for functions in this file */


int main(int argc, char **argv) {
    
    printf("This program is: %s\n", argv[0]);
    
    /* print warning if the number input parameters is not enough */
    if(argc < 5){
        printf("Input following information: training data file name, test data file name, output file name, k\n");
    }
    
    /* define input file name */
    char *trainer_data_filename = argv[1];
    char *trainee_data_filename = argv[2];
    
    /* define k for KNN */
    int k = atoi(argv[4]);
    
    /* report error for k <= 0 */
    if(k <= 0){
        printf("Error! Input should be positive!\n");
        exit(0);
    }
    
    /* define output file name */
    char *output_filename = argv[3];
    
    printf("Trainer file name is: %s\n", trainer_data_filename);
    printf("Trainee file name is: %s\n", trainee_data_filename);
    printf("The number of clusters is: %d\n", k);
    printf("Output file name is: %s\n", output_filename);
    
    info = (int*)malloc(5*sizeof(int));
    
    /* read size, dimention and numebr of labels of the data */
    read_raw_data(trainee_data_filename);
    read_trainer_data(trainer_data_filename);
    
    int attribute = info[0];
    int raw_size = info[1];
    int size = info[3];
    
    int raw_dimension = info[2];
    int dimension = info[4];

    /* report error for inconsistnent dimension of two sets */
    if(raw_dimension != dimension){
        printf("Data dimensions conflict!");
        return 0;
    }
    
    /* label one data each loop */
    for(int r = 0; r < raw_size; r++){
        
        /* create a priority queue to store distances*/
        Queue *distances =create_queue();
        
        /* calculate and store the distances */
        all_distances(size, dimension, r, distances);
        
        /* find k nearest neighbors to the data */
        count_neighbors(attribute, distances, k);
        
        /* free the priority queue */
        queue_free(distances);
        
        /* give the label of the data to the raw data set */
        label_node(raw_size, attribute, dimension, r);
    
    }
    
    /* write the results into the output file */
    write_data(raw_size, dimension, output_filename);
    
    /* print out the results */
    printf("k = %d:\n", k);
    printf("The following information has been written in the output file:\n");
    for(int i = 0; i < raw_size; i++){
        
        for(int j = 0; j < dimension; j++){
            printf("%lf,", raw_data[i][j]);
        }
        
        printf("%d\n", (int)raw_data[i][dimension]);
    }
    
    /* free all the arrays that we allocate space for */
    free_arrays();
    
    return 0;
}

