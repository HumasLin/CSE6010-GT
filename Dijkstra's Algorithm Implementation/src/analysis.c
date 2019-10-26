/*
 * analysis.c
 * For assignment 5
 * Created by Haomin Lin on 10/03/19.
 * Copyright © 2019 Haomin Lin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* include this file to conduct input string analysis */
#include "Dij.h"/* include Dij.h for functions in this file */
/*
* include queue.h to use the structure in this file
* this file is modified from the file created for Assignment 2
*/
#include "queue.h"

int main(int argc, char ** argv) {
    
    /* print warning if the number input parameters is not enough */
    if(argc < 2){
        printf("Input source data file name\n");
    }
    
    printf("This program is: %s\n", argv[0]);
    
    /* define input file name */
    char *source_data_file = argv[1];
    
    /* allocate space for file name from the command line input */
    char *output_file = (char*)malloc(100 * sizeof(char));
    
    /* define the output file name according to the command line input */
    if (argc >= 3 && argc <= 4) {
        if (strcmp(argv[2], "-o") == 0) {
            output_file = argv[3];
        }
        else{
            output_file = "output.txt";
        }
    }
    else{
        output_file = "output.txt";
    }
    
    /* initialize global variables */
    info = 0;
    maxi = 0;
    
    /* run the function to read source file */
    read_source_data(source_data_file);
    
    /* allocate space for the array storing priority queues of paths */
    paths = (Queue**)malloc(sizeof(info)* sizeof(Queue*));
    
    /* calculate the longest paths and largest distance from every node in the graph */
    for(int i = 0; i < info; i++){
        cal_distance(i);
    }
    
    /* print out the results */
    printf("The diameter = %lf\n", maxi);
    
    /* write the data to the output file */
    write_data(output_file);
}
