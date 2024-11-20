#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 9
#define MAX_SIZE 100

void countingSort(int arr[], int n) {
    int count[MAX_VALUE + 1] = { 0 };
    int* output = (int*)malloc(n * sizeof(int));

    // �p�ƨC�ӼƦr���X�{����
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // �p��ֿn����
    for (int i = 1; i <= MAX_VALUE; i++) {
        count[i] += count[i - 1];
    }

    // �N������J���T����m
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // �N���G�ƻs�^��}�C
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

int main() {
    int arr[MAX_SIZE];
    FILE* file = fopen("1_100.txt", "r");
    if (file == NULL) {
        printf("�L�k���}�ɮ�\n");
        return 1;
    }

    // Ū���ɮפ��e
    for (int i = 0; i < MAX_SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    printf("�Ƨǫe�����G:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // �p��Ƨǩһݮɶ�
    clock_t start, end;
    start = clock();

    countingSort(arr, MAX_SIZE);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ��X�Ƨǫ᪺���G
    printf("�Ƨǫ᪺���G:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // ��X�B��ɶ�
    printf("�B��ɶ�: %f ��\n", time_taken);

    return 0;
}
