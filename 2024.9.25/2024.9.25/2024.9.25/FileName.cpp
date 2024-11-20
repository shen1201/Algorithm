#include<stdio.h>
#include<stdlib.h>

int connected(int M[100][100] , int size);
void DFS(int M[100][100],int visit[100],int node , int size);
int connected_components(int M[100][100], int size);

int main() {
	int Array[100][100];

	FILE* fp;
	fp = fopen("01.txt", "r");
	int size;
	fscanf(fp, "%d", &size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fscanf(fp, "%d", &Array[i][j]);
		}
	}

	printf("adjacency matrix:\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", Array[i][j]);
		}
		printf("\n");
	}

	if (connected(Array, size)) {
		printf("a connected graph\n");
	}
	else {
		printf("Not a connected graph\n");
	}

	printf("%d connected components\n", connected_components(Array, size));

	return 0;
}

int connected(int M[100][100], int size) {
	int visit[100] = {};
	DFS(M, visit, 0, size);

	for (int i = 0; i < size; i++)
	{
		if (!visit[i]) {
			return 0;
		}
	}
	return 1;
}

void DFS(int M[100][100], int visit[100], int node, int size) {
	visit[node] = 1;

	for (int i = 0; i < size; i++)
	{
		if (M[node][i] == 1 && visit[i] != 1) {
			DFS(M, visit, i, size);
		}
	}
}

int connected_components(int M[100][100], int size) {
	int visit[100] = {};
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (!visit[i]) {
			DFS(M, visit, i, size);
			count++;
		}
	}

	return count;
}