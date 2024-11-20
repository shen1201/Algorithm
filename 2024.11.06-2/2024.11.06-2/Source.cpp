#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // 最多可以從檔案中讀取的元素數量
#define BITS 8   // 每個元素的位元數（8位元二進位）

// 根據給定的位數（exp）和基數對陣列進行計數排序的函數
void countSort(int arr[], int n, int exp, int base) {
    int output[2000]; // 用來暫存排序後元素的輸出陣列
    int count[2000]; // 用來存儲每個數字出現次數的陣列
    memset(count, 0, sizeof(count)); // 將計數陣列初始化為0

    // 計算在給定位置（exp）每個數字出現的次數
    for (int i = 0; i < n; i++) {
        int index = (arr[i] >> exp) & (base - 1); // 提取當前位置的數字
        count[index]++;
    }

    // 更新 count[i]，使其包含該數字在輸出陣列中的實際位置
    for (int i = 1; i < base; i++)
        count[i] += count[i - 1];

    // 通過將元素放置在正確的位置來構建輸出陣列
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] >> exp) & (base - 1); // 提取當前位置的數字
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // 將排序後的元素複製回原始陣列
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 對陣列進行基數排序的函數
void radixSort(int arr[], int n, int r) {
    int base = 1 << r; // 計算基數的值為 2^r（r 位元）
    for (int exp = 0; exp < BITS; exp += r) // 迭代每組 r 位元
        countSort(arr, n, exp, base); // 根據當前的位元組對陣列進行排序
}

int main() {
    FILE* file = fopen("2_100.txt", "r"); // 開啟輸入檔案以進行讀取
    if (file == NULL) { // 檢查檔案是否成功開啟
        printf("無法開啟檔案。\n");
        return 1; // 如果無法開啟檔案則退出程式
    }

    int arr[MAX]; // 用來存儲輸入元素的陣列
    int n = 0; // 用來追踪讀取的元素數量
    char line[20]; // 用來存儲從檔案中讀取的每行資料的緩衝區

    // 從檔案中讀取每行並將其從二進位字串轉換為整數
    while (fgets(line, sizeof(line), file) && n < MAX) {
        arr[n++] = (int)strtol(line, NULL, 2); // 將二進位字串轉換為整數
    }
    fclose(file); // 關閉輸入檔案



    int r = 2; // 每次排序使用的位元數（可以更改為 4 以進行 r = 4 的情況）
    radixSort(arr, n, r); // 對陣列進行基數排序

    // 列印排序後的陣列
    printf("\n排序後的陣列:\n");
    for (int i = 0; i < n; i++) {
        // 將排序後的數字轉換回二進制格式
        for (int j = BITS - 1; j >= 0; j--) {
            printf("%d", (arr[i] >> j) & 1);
        }
        printf("\n");
    }

    return 0; // 結束程式
}
