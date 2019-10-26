//
// Created by junzhu on 9/27/2019.
//

#include "graphgen.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * this function is to generate a weight in [w1, w2] uniformly;
 */
void generateWeight(EdgeNode *ENode) {
    double rand_weight;
    rand_weight = rand() / (double)(RAND_MAX) * (w_2 - w_1) + w_1;
    ENode->weight = rand_weight;
}

/**
 * this function is to generate all edge_nodes and store them;
 */
void genAllEdgeNodes() {
    all_edge_nodes = (EdgeNode**)malloc(N * sizeof(EdgeNode*));
    srand(1000000 * time(0));
    for (int i = 0; i < N; i++) {
        all_edge_nodes[i] = (EdgeNode*)malloc(sizeof(EdgeNode));
        all_edge_nodes[i]->data = i;
        all_edge_nodes[i]->next = NULL;
        generateWeight(all_edge_nodes[i]);
    }
}

/**
 * this function is to create a fully connected topology containing n0 nodes, n0 = 3;
 * Allocating space for some arrays defined in .h file;
 */
void initTopology() {
    //allocate space for graph_vertex[];
    graph_vertex = (VertexNode**)malloc(N * sizeof(VertexNode*));
    for (int i = 0; i < N; i++) {
        graph_vertex[i] = (VertexNode*)malloc(sizeof(VertexNode));
    }
    //allocate space for graph_degree[], and initialize it;
    graph_degree = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        graph_degree[i] = 0;
    }
    //construct initial topology;at first, there are 3 fully connected nodes in the graph;
    for (int i = 0; i < 3; i++) {
        graph_vertex[i]->data = i;
        if (i == 0) {
            graph_vertex[i]->first_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->next = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->data = 1;
            graph_vertex[i]->first_edge->weight = all_edge_nodes[1]->weight;
            graph_vertex[i]->first_edge->next->data = 2;
            graph_vertex[i]->first_edge->next->weight = all_edge_nodes[2]->weight;
        }
        if (i == 1) {
            graph_vertex[i]->first_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->next = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->data = 2;
            graph_vertex[i]->first_edge->weight = all_edge_nodes[2]->weight;
            graph_vertex[i]->first_edge->next->data = 0;
            graph_vertex[i]->first_edge->next->weight = all_edge_nodes[0]->weight;
        }
        if (i == 2) {
            graph_vertex[i]->first_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->next = (EdgeNode*)malloc(sizeof(EdgeNode));
            graph_vertex[i]->first_edge->data = 0;
            graph_vertex[i]->first_edge->weight = all_edge_nodes[0]->weight;
            graph_vertex[i]->first_edge->next->data = 1;
            graph_vertex[i]->first_edge->next->weight = all_edge_nodes[1]->weight;
        }
    }
    for (int i = 0; i < 3; i++) {
        graph_vertex[i]->first_edge->next->next = NULL;
    }
    //now 3 linked lists {0-1-2; 1-2-0; 2-0-1;} in graph_vertex[];
    size_graph = 3;
}

/**
 * this function is to calculate the degree of all nodes in the graph;
 */
void calDegree() {
    for (int i = 0; i < size_graph; i++) {
        int count = 0;
        if (graph_vertex[i] == NULL) {
            printf("Error! graph_vertex[%d] is empty!\n", i);
            exit(0);
        }
        EdgeNode *tmp1 = graph_vertex[i]->first_edge;
        if (tmp1 == NULL) {
            printf("Error! First edge is null!\n");
            exit(0);
        }
        count++;
        while (tmp1->next != NULL) {
            tmp1 = tmp1->next;
            count++;
        }
        graph_degree[i] = count;
    }

}

/**
 * this function is to add a specific data to the tail of linked list;
 */
void addTail(EdgeNode *ENode, VertexNode *VNode) {
    EdgeNode *tmp = VNode->first_edge;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (EdgeNode*)malloc(sizeof(EdgeNode));
    tmp->next->data = ENode->data;
    tmp->next->weight = ENode->weight;
    tmp->next->next = NULL;
    // ENode becomes a new vertex, and add it to graph_vertex[];
    graph_vertex[ENode->data]->data = ENode->data;
    graph_vertex[ENode->data]->first_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    graph_vertex[ENode->data]->first_edge->data = all_edge_nodes[VNode->data]->data; //let last VNode become its first edge;
    graph_vertex[ENode->data]->first_edge->weight = all_edge_nodes[VNode->data]->weight;
    graph_vertex[ENode->data]->first_edge->next = NULL;
    size_graph++;
}

/**
 * this function is to calculate the sum of all degree in this graph;
 */
int sumAllDegree() {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += graph_degree[i];
    }
    return sum;
}

/**
 * this function is to generate prob_nodes[] and interval_prob[];
 * and store probability and interval in them;
 */
void generateProb() {
    calDegree();
    //allocate and initialize;
    for (int i = 0; i < N; i++) {
        prob_nodes[i] = 0;
    }
    for (int i = 0; i < N+1; i++) {
        interval_prob[i] = 0;
    }
    //compute probability and store them;
    for (int i = 0; i < size_graph; i++) {
        prob_nodes[i] = (double) graph_degree[i] / (double) sumAllDegree();
    }
    for (int i = 0; i < size_graph + 1; i++) {
        if (i == 0) {
            interval_prob[i] = 0;
            continue;
        }
        interval_prob[i] = interval_prob[i - 1] + prob_nodes[i - 1];
    }
}

/**
 * this function is to add a node in round i to the graph;
 * round i >= 3;
 */
void addNodeToGraph(int round) {
    //the node to be added is all_edge_nodes[round];
    generateProb();
    int i = 0;
    int tmp_v; // to record which vertex this node should connect with;
    srand( 1000000 * round * (round+2) * (unsigned int)time(0));
    double p = (double) rand() /(double) RAND_MAX; // 0 < p < 1;
    while (1) {
        if (interval_prob[i] > interval_prob[i+1]) {
            printf("Select Vertex failed!\n");
            exit(0);
        }
        if (i > size_graph) {
            printf("Cannot connect!\n");
            exit(0);
        }
        if (p >= interval_prob[i] && p < interval_prob[i+1]) {
            tmp_v = i;
            break;
        } else {
            i++;
        }
    }
    addTail(all_edge_nodes[round], graph_vertex[tmp_v]);
}

/**
 * this function is to print the graph out;
 */
void printGraph() {
    for (int i = 0; i < size_graph; i++) {
        printf("%d ", graph_vertex[i]->data);
        if (graph_vertex[i]->first_edge != NULL) {
            EdgeNode *tmp = graph_vertex[i]->first_edge;
            while (tmp != NULL) {
                printf("%d ", tmp->data);
                tmp = tmp->next;
            }
        }
        printf("\n");
    }
}

/**
 * this function is to write all nodes in this graph to output file;
 */
void writeTopology(char *out_file_name) {
    char file_path[100];
    FILE **cluster_files = (FILE**)malloc(sizeof(FILE*)); //points to each cluster file which stores cluster data;
    if (cluster_files == NULL) {
        printf("Creating cluster_files failed!\n");
        exit(0);
    }
    //write file path to file_path[]
    sprintf(file_path, out_file_name);
    cluster_files[0] = fopen(file_path, "w");
    //write attribute
    fprintf(cluster_files[0], "%d\n", size_graph);
    //write information of each data to cluster_files[0];
    for (int i = 0; i < 3; i++) {
        fprintf(cluster_files[0], "%d %d ", graph_vertex[i]->data, graph_degree[i]);
        if (i == 0) {
            fprintf(cluster_files[0], "%d %lf %d %lf ", all_edge_nodes[1]->data, all_edge_nodes[1]->weight,
                                                                      all_edge_nodes[2]->data, all_edge_nodes[2]->weight);
        }
        if (i == 1) {
            fprintf(cluster_files[0], "%d %lf %d %lf ", all_edge_nodes[2]->data, all_edge_nodes[2]->weight,
                                                                      all_edge_nodes[0]->data, all_edge_nodes[1]->weight);
        }
        if (i == 2) {
            fprintf(cluster_files[0], "%d %lf %d %lf ", all_edge_nodes[0]->data, all_edge_nodes[2]->weight,
                                                                      all_edge_nodes[1]->data, all_edge_nodes[2]->weight);
        }
        EdgeNode *tmp = graph_vertex[i]->first_edge->next->next;
        for (int j = 0; j < graph_degree[i]-2; j++) {
            if (tmp == NULL) {
                break;
            } else {
                fprintf(cluster_files[0], "%d %lf ", tmp->data, tmp->weight);
                tmp = tmp->next;
            }
        }
        fprintf(cluster_files[0], "\n");
    }

    for (int i = 3; i < size_graph; i++) {
        fprintf(cluster_files[0], "%d %d ", graph_vertex[i]->data, graph_degree[i]);
        EdgeNode *tmp = graph_vertex[i]->first_edge;
        fprintf(cluster_files[0], "%d %lf ", tmp->data, all_edge_nodes[i]->weight);
        tmp = tmp->next;
        for (int j = 0; j < graph_degree[i]-1; j++) {
            if (tmp == NULL) {
                break;
            } else {
                fprintf(cluster_files[0], "%d %lf ", tmp->data, tmp->weight);
                tmp = tmp->next;
            }
        }
        fprintf(cluster_files[0], "\n");
    }
    //after writing, close ths file;
    fclose(cluster_files[0]);
}

/**
 * a helper function to check if this array contains a value;
 */
int isContain(int d, int *degree_number) {
    for (int i = 0; i < size_graph; i++) {
        if (d == degree_number[i]) {
            return 1;
        }
    }
    return 0;
}

/**
 * this function is to write a histogram output file;
 * each line contains the value of degree, the number of nodes with this degree, all nodes;
 */
void writeHistogram (char *histo_out_name) {
    //degree_number[] is to store all different degrees;
    int *degree_number = (int*)malloc(size_graph * sizeof(int));
    for (int i = 0; i < size_graph; i++) {
        degree_number[i] = 0;
    }
    int j = 0;
    for (int i = 0; i < size_graph; i++) {
        int tmp = graph_degree[i];
        if (isContain(tmp, degree_number) == 0) { //which means degree_number[] has no tmp;
            degree_number[j] = tmp;
            j++;
        }
    }
    //nodes_number[] is to store the number of nodes with a specific degree;
    int *nodes_number = (int*)malloc((j+1) * sizeof(int));
    for (int i = 0; i < (j+1); i++) {
        nodes_number[i] = 0;
    }
    for (int i = 0; i < size_graph; i++) {
        for (int k = 0; k < (j+1); k++) {
            if (graph_degree[i] == degree_number[k]) {
                nodes_number[k]++;
            }
        }
    }
    //it's time to write them to histogram file;
    char file_path[100];
    FILE **cluster_files = (FILE**)malloc(sizeof(FILE*)); //points to each cluster file which stores cluster data;
    if (cluster_files == NULL) {
        printf("Creating cluster_files failed!\n");
        exit(0);
    }
    //write file path to file_path[]
    sprintf(file_path, histo_out_name);
    cluster_files[0] = fopen(file_path, "w");
    //write attributes
    for (int i = 0; i < j; i++) {
        fprintf(cluster_files[0], "%d %d ", degree_number[i], nodes_number[i]);
        for (int k = 0; k < size_graph; k++) {
            if (graph_degree[k] == degree_number[i]) {
                fprintf(cluster_files[0], "%d ", k);
            }
        }
        fprintf(cluster_files[0], "\n");
    }
}


