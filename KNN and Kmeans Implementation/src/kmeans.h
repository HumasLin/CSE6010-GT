//
// Created by jzhsi on 9/17/2019.
//

#ifndef A4_KMEANS_H
#define A4_KMEANS_H

int data_size; // the number of data in txt file;
double *disToCenter;
int dimension;
int *data_cluster_type;
int *center_cluster_type;
double **data; // to store each dada;
double **cluster_centroid; // to store each cluster center
int K; //the number of clusters
int *num_cluster_items;
int *items_in_cluster; //to store the number of each cluster;

/**
 * get the dimension and data_size from this K-means file;
 */
void preProcess(char* file_name);

/**
 * read 250 data, and store their value to data[];
 */
void readData(char *file_name);

/**
 * initialize K centroids randomly, and each centroid is unique;
 */
void initializeCentroid(char *file_name);

/**
 * compute distances from one data to all centers;
 * disToCenter[] stores distances;
 */
void allDistance(int data_ID);

/**
 * after computing the distance from one data to all centers, then find and change its center_type;
 */
void updateOneDataType(int data_ID);

/**
 * computing distances from all data to all centers, and update their cluster type;
 */
void updateAllDataType(int round);

/**
 *After one round of training, write these data to output file;
 */
void writeTrainedData(int K, char *outfile);

/**
 * re-calculate centers of all clusters;
 */
void reCalCenters(int round);

/**
 * this function is to compute the sum of root-mean-square of each cluster;
 */
double sumRMS();

/**
 * this function is to judge if kmeans should stop or not;
 * if we should stop, return 1; else, return 0;
 */
int judgeKmeans(double preRMS, double nowRMS);


#endif //A4_KMEANS_H
