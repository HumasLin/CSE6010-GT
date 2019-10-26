/*
 * KNN.c
 * For assignment 4
 * Created by Haomin Lin on 9/22/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "KNN.h"
#include "queue.h"/* include two .h files for functions in this file */

/*
 * define function all_distances
 */
void all_distances(int size, int dimension, int r, Queue *distances){
    
    /* declare variables */
    int attribute_now = 0;
    double distance;
    
    for(int i = 0; i < size; i++){
        
        double od_distance = 0.0;
            
        for(int j = 0; j < dimension + 1; j++){
            
            /* calculate distance for each dimension */
            if(j < dimension){
                od_distance += (raw_data[r][j] - trainer_data[i][j]) * (raw_data[r][j] - trainer_data[i][j]);
            }
            
            /* assign the label to a variable for later use */
            else{
                attribute_now = trainer_data[i][j];
            }
        }
        
        /* calculate square root of the distance */
        distance = sqrt(od_distance);
        
        /* put the distance and label into the priority queue */
        queue_insert(distances, distance, attribute_now);
        
    }
}

/*
 * define function count_neighbors
 */
void count_neighbors(int attribute, Queue* distances, int k){
    
    /* initialize and allocate space for array sum */
    for(int j = 0; j < attribute; j++){
        sum = (int*)malloc(attribute*sizeof(int));
        sum[j] = 0;
    }
   
    /* define an array for comparison */
    int counter[attribute];
    for(int j = 0; j < attribute; j++){
        counter[j] = j;
    }
    
    /* count the first k nearest neighbors in each cluster */
    for(int j = 0; j < k; j++){
        
        for(int i = 0; i < attribute; i++){

            int follow = counter[i];/* initialize the variable for comparison */
                    
            if(distances->next->attr == follow){
                            
                int m = distances->next->attr;
                            
                sum[m] += 1;/* add one for corresponding cluster */
                    
                remove_queue(distances);
                /* remove the currently nearest one in the queue so that next time we can still read the currently nearest one directly*/
                
                break;
                        
            }
        }
    }
}

/*
 * define function label_node
 */
void label_node(int raw_size, int attribute, int dimension, int r){
    
    /* declare variables */
    int d = 0;
    int sum_max = 0;
    
    /* find the cluster that has most nearest neighbors*/
    for(int s = 0; s < attribute; s++){
        if (sum[s] != 0) {
            if(sum[s] >= sum_max){
                sum_max = sum[s];
                d = s;
            }
        }
    }
    raw_data[r][dimension] = d;/* give the label to the raw data */
}


void read_raw_data(char* file_name){
    
    /* declare variables */
//    int dimension = 0;
//    int size = 0;
//
    FILE *fread = fopen(file_name, "r");
    
    /* report error if file open fails */
    if(fread == NULL){
        printf("No data!\n");
        exit(0);
    }
    
    /*
     * read the size and dimension for later use
     * the raw data only holds size and dimension
     */
    fscanf(fread, "%d %d", &info[1], &info[2]);
    
    /* allocate space for two dimension arrays */
    raw_data = (double**)malloc(info[1] * sizeof(double*));
    for(int i = 0; i < info[1]; i++){
        raw_data[i] = (double*)malloc((info[2] + 1)*sizeof(double));
    }
    
    /* put the read data into the array */
    for(int i = 0; i < info[1]; i++){
        for(int j = 0; j < info[2]; j++){
            fscanf(fread, "%lf", &raw_data[i][j]);
        }
    }
}

/*
 * define function read_trainer_data
 */
void read_trainer_data(char* file_name){
    
    /* declare variables */
//    int dimension = 0;
//    int size = 0;
//    int attr = 0;
    
    FILE *fread = fopen(file_name, "r");
    
    if(fread == NULL){
        printf("No data!\n");
        exit(0);
    }
    
    /*
     * read the size and dimension for later use
     * the raw data holds size, dimension, and number of labels
     */
    fscanf(fread, "%d %d %d", &info[0], &info[3], &info[4]);
    
    /* allocate space for two dimension arrays */
    trainer_data = (double**)malloc(info[3] * sizeof(double*));
    for(int i = 0; i < info[3]; i++){
        trainer_data[i] = (double*)malloc((info[4] + 1)*sizeof(double));
    }
    
    /* put the read data into the array */
    for(int i = 0; i < info[3]; i++){
        for(int j = 0; j < info[4] + 1; j++){
            fscanf(fread, "%lf", &trainer_data[i][j]);
        }
    }
}

/*
 * define function write_data
 */
void write_data(int raw_size, int dimension, char *outfile){
    
    FILE* fwrite = fopen(outfile, "w");
    
    /* report error if file creation fails */
    if (fwrite == NULL){
        printf("Failed!");
    }
    
    /* write the trained data into output files */
    for(int i = 0; i < raw_size; i++){
        
        for(int j = 0; j < dimension; j++){
            fprintf(fwrite, "%lf,", raw_data[i][j]);
            /* write the coordinates*/
        }
        fprintf(fwrite, "%d\n", (int)raw_data[i][dimension]);
        /* write the dimension */
    }
    
    fclose(fwrite);
}

/*
 * define function free_arrays
 */
void free_arrays(){
    
    for(int i = 0; i < info[1]; i++){
        free(raw_data[i]);
    }
    free(raw_data);
    
    for(int i = 0; i < info[3]; i++){
        
        free(trainer_data[i]);
        
    }
    free(trainer_data);
    
    free(sum);

    free(info);
}
