#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 9
#define MAX_SIZE 100

void countingSort(int arr[], int n) {
    int count[MAX_VALUE + 1] = { 0 };
    int* output = (int*)malloc(n * sizeof(int));

    // 計數每個數字的出現次數
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 計算累積次數
    for (int i = 1; i <= MAX_VALUE; i++) {
        count[i] += count[i - 1];
    }

    // 將元素放入正確的位置
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 將結果複製回原陣列
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

int main() {
    int arr[MAX_SIZE];
    FILE* file = fopen("1_100.txt", "r");
    if (file == NULL) {
        printf("無法打開檔案\n");
        return 1;
    }

    // 讀取檔案內容
    for (int i = 0; i < MAX_SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    printf("排序前的結果:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // 計算排序所需時間
    clock_t start, end;
    start = clock();

    countingSort(arr, MAX_SIZE);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // 輸出排序後的結果
    printf("排序後的結果:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 輸出運行時間
    printf("運行時間: %f 秒\n", time_taken);

    return 0;
}
