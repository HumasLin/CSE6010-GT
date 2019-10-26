//
// Created by junzhu on 9/17/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"
#include <math.h>

/**
 * get the dimension and data_size from this K-means file;
 */
void preProcess(char* file_name) {
    FILE *fread = fopen(file_name, "r");
    if (fread == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fread, "%d %d ", &data_size, &dimension);
}

/**
 * read 250 data, and store their value to data[];
 */
void readData(char *file_name) {
    FILE *fread = fopen(file_name, "r");
    //Allocating space for data[][];
    data = (double**)malloc(data_size * sizeof(double*));
    for (int i = 0; i < data_size; i++) {
        data[i] = (double*)malloc(dimension  * sizeof(double));
    }
    data_cluster_type = (int*)malloc(data_size * sizeof(int));
    int a, b;
    for (int i = 0; i < data_size + 1; i++) {
        //do not need to read the first line; first line just contains two values;
        if (i == 0) {
            fscanf(fread, "%d %d", &a, &b); // just discard a and b, because we have got size and dimension;
            continue;
        }
        for (int j = 0; j < dimension; j++) {
            fscanf(fread, "%lf", &data[i - 1][j]);
        }
        //initialize cluster_type; At first, every data belongs to cluster type = -1;
        data_cluster_type[i-1] = -1;
    }
}

/**
 * initialize K centroids randomly, and each centroid is unique;
 */
void initializeCentroid(char *file_name) {
    center_cluster_type = (int*)malloc(K * sizeof(int));
    FILE *fread = fopen(file_name, "r");
    //cluster_centroid[][] stores each centroid as a type of data;
    cluster_centroid = (double**)malloc(K * sizeof(double*));
    for (int i = 0; i < K; i++) {
        cluster_centroid[i] = (double*)malloc(dimension * sizeof(double));
    }
    //initialize first K centroids;
    int a, b;
    for (int i = 0; i < K + 1; i++) {
        //do not need to read the first line; first line just contains two values;
        if (i == 0) {
            fscanf(fread, "%d %d", &a, &b); // just discard a and b, because we have got size and dimension;
            continue;
        }
        for (int j = 0; j < dimension; j++) {
            fscanf(fread, "%lf", &cluster_centroid[i - 1][j]);
        }
        center_cluster_type[i - 1] = i - 1;
        data_cluster_type[i - 1] = i;
    }
}

/**
 * compute distances from one data to all centers;
 * disToCenter[] stores distances;
 */
void allDistance(int data_ID) {
    disToCenter = (double*)malloc((K) * sizeof(double));
    for (int i = 0; i < K; i++) {
        disToCenter[i] = (double)0;
    }
    for (int i = 0; i < K; i++) {
        double tmp_sum = 0;
        for (int j = 0; j < dimension; j++) {
            tmp_sum += (double)pow((data[data_ID][j] - cluster_centroid[i][j]),2);
        }
        disToCenter[i] = (double)(tmp_sum);
    }
}

/**
 * after computing the distance from one data to all centers, then find and change its center_type;
 */
void updateOneDataType(int data_ID) {
    double min = disToCenter[0];
    int min_index = 0;
    for (int i = 0; i < K; i++) {
        if (min > disToCenter[i]) {
            min = disToCenter[i];
            min_index = i;
        }
    }
    data_cluster_type[data_ID] = min_index;
    items_in_cluster[data_cluster_type[data_ID]]++;
}

/**
 * computing distances from all data to all centers, and update their cluster type;
 */
void updateAllDataType(int round) {
    items_in_cluster = (int*)malloc(K * sizeof(int));
    for (int i = 0; i <K; i++) {
        items_in_cluster[i] = 0;
    }
    for (int i = 0; i < data_size; i++) {
            allDistance(i);
            updateOneDataType(i);
    }
}

/**
 *After one round of training, write these data to output file;
 */
void writeTrainedData(int K, char *outfile) {
    char file_path[100];
    FILE **cluster_files = (FILE**)malloc(sizeof(FILE*)); //points to each cluster file which stores cluster data;
    if (cluster_files == NULL) {
        printf("Creating cluster_files failed!\n");
        exit(0);
    }
    //write file path to file_path[]
    sprintf(file_path, outfile);
    cluster_files[0] = fopen(file_path, "w");
    //write attribute
    fprintf(cluster_files[0], "%d %d %d\n", K, data_size, dimension);
    //write information of each data to cluster_files[K];
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < dimension; j++) {
            fprintf(cluster_files[0], "%lf ", data[i][j]);
        }
        fprintf(cluster_files[0], "%d \n", data_cluster_type[i]);
    }
    //after writing, close ths file;
    fclose(cluster_files[0]);
}

/**
 * re-calculate centers of all clusters;
 */
void reCalCenters(int round) {
    //store the number of items in each cluster;
    num_cluster_items = (int*)malloc(K * sizeof(int));
    for (int i = 0; i < K; i++) {
        num_cluster_items[i] = 0;
    }
    //sum_dimension helps store sum of dimensions and new centers' coordinates;
    double **sum_dimension;
    sum_dimension = (double**)malloc((dimension+1) * sizeof(double*));
    for (int i = 0; i < dimension; i++) {
        sum_dimension[i] = (double*)malloc((K+1) * sizeof(double));
    }
    //initialize;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < K; j++) {
            sum_dimension[i][j] = 0;
        }
    }
    //add the value of every dimension to sum_dimension[][];
    for (int d = 0; d < dimension; d++) {
        for (int k = 0; k < data_size; k++) {
            sum_dimension[d][data_cluster_type[k]] += data[k][d];
        }
    }
    //record the size of each cluster;
    for (int i = 0; i < data_size; i++) {
        num_cluster_items[data_cluster_type[i]]++;
    }
    //recompute centers' coordinates;
    for (int d = 0; d < dimension; d++) {
        for (int k = 0; k < K; k++) {
            sum_dimension[d][k] = sum_dimension[d][k] / (double)num_cluster_items[k];
            cluster_centroid[k][d] = sum_dimension[d][k];
        }
    }
}

/**
 * this function is to compute the sum of root-mean-square of each cluster;
 */
double sumRMS() {
    double sum = 0;
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < dimension; j++) {
            sum += pow((data[i][j] - cluster_centroid[data_cluster_type[i]][j]),2);
        }
    }
    return sum;
}

/**
 * this function is to judge if kmeans should stop or not;
 * if we should stop, return 1; else, return 0;
 */
int judgeKmeans(double preRMS, double nowRMS) {
    if (preRMS != nowRMS) {
        return 0;
    }
    if (preRMS == nowRMS) {
        return 1;
    }
    return 0;
}