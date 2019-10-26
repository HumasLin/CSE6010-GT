Authors: Junzhu Xiang, Haomin Lin
Created: 9/17/2019
Last modified: 9/27/2019
Affiliation: Georgia Institute of Technology
Operating system: Linux

Description:
-------------
In this assignment, we applied algorithms of Kmeans and KNN to identify and classify data of Old Faithful geyser's eruption. First, we used Kmeans to classify these data by setting K as the cluster number and label them; Second, we used KNN to classify 22 test data and label them by using the output file produced by Kmeans.
In the zip file, faithful-Kmeans-4.txt and faithful-KNN-4.txt are used to test when data has 4 dimensions. And Kmeans_data_test.txt file is created by author, and it is used to test the correctness of Kmeans part.
After 4 steps below, you can get two files, one is Kmeans_out.txt, which labelled every data; another one is KNN_out.txt, which labelled the data from faithful-KNN.txt.

Installation:
------------
To compile and run this software, you should use Deepthought cluster. 
Note: these 4 steps below are used to compile and run original data sets from faithful-Kmeans.txt and faithful-KNN.txt, if you want to use test data sets files (also in the zip file) to verify my program, you can simply replace with them.
There are 4 steps:
(1) Run:
------------
gcc -lm kmeans.c main_kmeans.c -std=c99 -o A4_0
Note: The -std=c99 flag is required on some C compilers to allow variable declarations at arbitrary locations in a function.

(2) Execution:
------------
./A4_0 faithful-Kmeans.txt 2 Kmeans_out.txt
Note: faithful-Kmeans.txt is the input file; 2 is the number of clusters; Kmeans_out.txt is the output file produced by Kmeans.

(3) Run:
------------
gcc -lm KNN.c queue.c main_knn.c -std=c99 -o A4_1

(4) Execution:
------------
./A4_1 Kmeans_out.txt faithful-KNN.txt KNN_out.txt 11
Note: K in (4), which is 11, is different from K in (2). And KNN_out.txt is the output file produced by KNN, and it labeled 22 data to each cluster.
