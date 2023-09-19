#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int V; // 그래프의 정점 수
int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j, char buffer[], int *len);
void findShortestPath(int graph[7][7], int src, int dest, int *len, char buffer[]);