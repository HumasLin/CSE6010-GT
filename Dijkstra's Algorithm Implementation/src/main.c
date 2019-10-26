#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphgen.h"
#include <string.h>

int main(int argc, char* argv[]) {
    //select time as random see;
    srand( 1000000*(unsigned int)time(0));
    //allocate for the output files;
    char *out_file_name = (char*)malloc(100 * sizeof(char));
    char *histo_out_name = (char*)malloc(100 * sizeof(char));

    printf("This program is: %s\n",argv[0]);
    //N should be a positive integer;
    N = atoi(argv[1]);
    if (N <= 0) {
        printf("Error! N must be a positive integer!\n");
        exit(0);
    }
    w_1 = atof(argv[2]);
    if (w_1 <= 0) {
        printf("Error! w_1 should be larger than 0!\n");
        exit(0);
    }
    w_2 = atof(argv[3]);
    if (w_2 <= 0) {
        printf("Error! w_2 should be larger than 0!\n");
        exit(0);
    }
    if (w_2 < w_1) {
        printf("Error! w_2 must be larger or equal to w_1!\n");
        exit(0);
    }

    //code below is to write output files;
    int o = 1;
    int h = 1; //if o, h == 0, write;
    if (argc >= 6 && argc <=7) {
        if (strcmp(argv[4], "-o") == 0 && strcmp(argv[5], "-o") != 0 && strcmp(argv[5], "-h") != 0) {
            out_file_name = argv[5];
            o = 0;
        }
        if (strcmp(argv[4], "-h") == 0 && strcmp(argv[5], "-o") != 0 && strcmp(argv[5], "-h") != 0) {
            histo_out_name = argv[5];
            h = 0;
        }
        if (argc == 7) {
            if (strcmp(argv[5], "-o") == 0 && strcmp(argv[6], "-o") != 0 && strcmp(argv[6], "-h") != 0) {
                out_file_name = argv[6];
                o = 0;
            }
            if (strcmp(argv[5], "-h") == 0 && strcmp(argv[6], "-o") != 0 && strcmp(argv[6], "-h") != 0) {
                histo_out_name = argv[6];
                h = 0;
            }
        }
    }
    if (argc == 8) {
        if (strcmp(argv[4], "-o") == 0) {
            out_file_name = argv[5];
            o = 0;
        }
        if (strcmp(argv[4], "-h") == 0) {
            histo_out_name = argv[5];
            h = 0;
        }
        if (strcmp(argv[6], "-o") == 0) {
            out_file_name = argv[7];
            o = 0;
        }
        if (strcmp(argv[6], "-h") == 0) {
            histo_out_name = argv[7];
            h = 0;
        }
    }
    //if there is no "-o" in the command, then output "topology.txt"
    if (o == 1) {
        out_file_name = "topology.txt";
        o = 0;
    }

    prob_nodes = (double*)malloc(N * sizeof(double));
    interval_prob = (double*)malloc((N+1) * sizeof(double));
    genAllEdgeNodes();
    initTopology();

    //generate the whole graph;
    for (int i = 3; i < N; i++) {
        addNodeToGraph(i);
    }
    printf("\n");
    printf("The graph is below:\n");
    printGraph();
    calDegree();
    printf("\n");

    //write data to output files; if o == 0, then write topology;
    if (o == 0) {
        writeTopology(out_file_name);
    }
    //if h == 0, then write histogram;
    if (h == 0) {
        writeHistogram(histo_out_name);
    }
    return 0;
}