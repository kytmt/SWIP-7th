#include "rpi_1_dijkstra.h"

int readTxtFile(void)
{
    FILE *file = fopen("map_data.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return 1;
    }
    fscanf(file, "%d", &V);
    // 파일에서 그래프 데이터 읽기
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j, char buffer[], int *len) {
    if (parent[j] == -1) {
        (*len) += sprintf(buffer + (*len), "%d", j);
        printf("%d", j);
        return;
    }

    printPath(parent, parent[j], buffer, len);
    (*len) += sprintf(buffer + (*len), " -> %d", j);
    printf(" -> %d", j);
}

void findShortestPath(int src, int dest, char buffer[], int *len) {

    readTxtFile();

    int dist[V]; // 최단 거리를 저장하는 배열
    int sptSet[V]; // 최단 경로 트리에 포함된 정점을 나타내는 배열
    int parent[V]; // 최단 경로를 저장하는 배열

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX; // 모든 거리를 무한대로 초기화
        sptSet[i] = 0; // 최단 경로 트리에 포함되지 않음
        parent[i] = -1; // 최단 경로 초기화
    }

    dist[src] = 0; // 시작 정점의 거리는 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // 최단 경로 업데이트
            }
        }
    }

    *len = 0; // 문자열 길이 초기화

    printf("The shortest path is ");
    // 최단 경로 문자열 생성
    (*len) += sprintf(buffer + (*len), "The shortest path is ");
    printPath(parent, dest, buffer, len);
    printf("\n");
}

/*
int main() {
    char temp[1024]; // 문자열 저장 배열
    int src = 3; // 시작 노드
    int dest = 6; // 도착 노드
    int len; // 문자열 길이

    findShortestPath(src, dest, temp, &len); // 시작 노드와 도착 노드를 지정하여 최단 경로 계산

    printf("len : %d\n",len);

    return 0;
}
*/