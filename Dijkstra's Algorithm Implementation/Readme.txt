Authors: Junzhu Xiang, Haomin Lin
Created: 9/27/2019
Last modified: 10/9/2019
Affiliation: Georgia Institute of Technology
Operating system: Linux

Description:
-------------
In this assignment, we generate scale free network graph randomly and use linked lists to store this graph. After that, we pass a topology
file from part 1 to part 2 of this software. Then we apply Dijkstra algorithm to analyze the diameter of this graph.

Installation:
------------
Note: To compile and run this software, you should use Deepthought cluster. These 4 steps:

(1) Run:
------------
gcc -lm graphgen.c main.c -std=c99 -o graphgen
Note: The -std=c99 flag is required on some C compilers to allow variable declarations at arbitrary locations in a function.

(2) Execution:
------------
./graphgen N W_1 W_2 -o top.txt -h histo.txt
Note: In the command line above, the second parameter N is the number of nodes in this graph, and it must be a positive integer, like 10, 200, 500，and so on.
The third parameter W_1 is the lower bound of link's weight, and the fourth parameter W_2 is the upper bound of link's weight. Their type is double. And 
they must be larger than 0, and W_2 must be larger or equal to W_1. After that, the output files are optional. You can input "-o filename.txt" to get the topology 
of the graph, if you don't input -o, you will get a topology file named "topology.txt". You can input "-h filename.txt" to get the histogram file of nodes' distribution, 
if you don't input -h, you will get nothing. 

(3) Run:
------------
gcc -lm Dij.c queue.c analysis.c -std=c99 -o analysis

(4) Execution:
------------
./analysis top.txt -o output.txt
Note: the second parameter in the command line is the output file from step 2, which stores the topology of this scale free network graph. After that, output file 
is optional. If you want to get more detailed information about the graph, you should input "-o filename.txt" after second parameter, and if you don't input 
"-o", you will get a output file named "output.txt".