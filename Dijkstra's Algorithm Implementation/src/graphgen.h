//
// Created by junzhu on 9/27/2019.
//

#ifndef A5_GRAPHGEN_H
#define A5_GRAPHGEN_H

typedef struct EdgeNode {
    int data;
    double weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
    int data;
    struct EdgeNode *first_edge;
} VertexNode;

VertexNode **graph_vertex; //to store every vertex of this graph;
int *graph_degree; //to store the degree of every node in this graph;
int N; // N is maximum number of nodes in this graph;
double w_1, w_2; // the lower and upper bound of weight;
int size_graph; // to record current number of items in the graph;
double *prob_nodes; // to store p(i) of every node i, which is d(i)/D;
double *interval_prob; // a helper array, to help which node should be connected;
EdgeNode **all_edge_nodes; // to store N edge nodes;

/**
 * this function is to generate a weight in [w1, w2] uniformly;
 */
void generateWeight(EdgeNode *ENode);

/**
 * this function is to generate all edge_nodes and store them;
 */
void genAllEdgeNodes();

/**
 * this function is to create a fully connected topology containing n0 nodes, n0 = 3;
 * Allocating space for some arrays defined in .h file;
 */
void initTopology();

/**
 * this function is to add a specific data to the tail of linked list;
 */
void addTail(EdgeNode *ENode, VertexNode *VNode);

/**
 * this function is to calculate the sum of all degree in this graph;
 */
int sumAllDegree();

/**
 * this function is to generate prob_nodes[] and interval_prob[];
 * and store probability and interval in them;
 */
void generateProb();

/**
 * this function is to add a node in round i to the graph;
 * round i >= 3;
 */
void addNodeToGraph(int round);

/**
 * this function is to print the graph out;
 */
void printGraph();

/**
 * this function is to calculate the degree of all nodes in the graph;
 */
void calDegree();

/**
 * this function is to write all nodes in this graph to output file;
 */
void writeTopology(char *out_file_name);

/**
 * this function is to write a histogram output file;
 * each line contains the value of degree, the number of nodes with this degree, all nodes;
 */
void writeHistogram (char *histo_out_name);


#endif //A5_GRAPHGEN_H
