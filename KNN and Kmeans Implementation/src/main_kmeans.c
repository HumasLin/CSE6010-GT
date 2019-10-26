#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"

int main(int argc, char* argv[])
{
    printf("This program is: %s\n",argv[0]);
    if (argc < 4) {
        printf("You need to input three parameters: input file, K, and output file!\n");
        exit(0);
    }
    char *input_file_name = argv[1];
    K = atoi(argv[2]);
    if (K <= 0) {
        printf("Error! K must be a positive integer!\n");
        exit(0);
    }
    char *output_file_name = argv[3];
    printf("Input file name is: %s\n", input_file_name);
    printf("The number of clusters is: %d\n", K);
    printf("Output file name is: %s\n", output_file_name);

    int max_round = 100; // if training times exceeds max_round, program should stop;
    double sumrms = 0; //Root mean square;
    int stop_round; //to record the round when the training stops;
    double preRMS = 0; //to record previous RMS;
    double nowRMS = 0; //to record current RMS;

    preProcess(input_file_name);
    if (K > data_size) {
        printf("Error! K is %d, data_size is %d!", K, data_size);
        exit(0);
    }
    readData(input_file_name);
    initializeCentroid(input_file_name); //now data[0] to data[9], their cluster is 1 to 9;
    updateAllDataType(0); // initialize every data's cluster type;
    printf("\nAfter initializing, size of each cluster: \n");
    for (int i = 0; i < K; i++) {
        printf("%d ", items_in_cluster[i]);
    }
    printf("\nAfter initializing, coordinates of each center:\n");
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%lf ", cluster_centroid[i][j]);
        }
        printf("\n");
    }
    printf("\n********************now start training!********************\n");

    //now start training;
    for (int i = 0; i < max_round; i++) {
        preRMS = sumRMS();
        reCalCenters(i);
        updateAllDataType(i);
        //after one round training, print the size of each cluster and coordinates of each center;
        printf("\nsize of each cluster: \n");
        for (int i = 0; i < K; i++) {
            printf("%d ", items_in_cluster[i]);
        }
        printf("\ncoordinates of each center:\n");
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < dimension; j++) {
                printf("%lf ", cluster_centroid[i][j]);
            }
            printf("\n");
        }
        nowRMS = sumRMS();
        //judge if training should stop;
        if (judgeKmeans(preRMS, nowRMS) == 1) {
                stop_round = i;
                printf("root mean square = %lf\n",sumRMS());
                printf("\nAfter %d round training, Root Mean Square doesn't change!\n", stop_round);
                break;
        }
        if (i == max_round - 1) {
            printf("After %d round training, we cannot get the best result!\n", max_round);
        }
        printf("root mean square = %lf\n",sumRMS());
        sumrms += sumRMS();
    }

    writeTrainedData(K, output_file_name);

    return 0;
}
