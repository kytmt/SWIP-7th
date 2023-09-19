#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int V; // 그래프의 정점 수
int graph[8][8];
int readTxtFile(void);
int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j, char buffer[], int *len);
void findShortestPath(int src, int dest, char buffer[], int *len);