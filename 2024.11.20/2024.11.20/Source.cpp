#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000  // 假設最多有 1000 筆數據

// 定義一個節點結構以處理桶中的多個數字
typedef struct Node {
    float value;
    struct Node* next;
} Node;

// 創建一個節點
Node* createNode(float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// 插入數字到桶中（插入排序以保持排序狀態）
void insertNode(Node** bucket, float value) {
    Node* newNode = createNode(value);
    if (*bucket == NULL || (*bucket)->value >= value) {
        newNode->next = *bucket;
        *bucket = newNode;
    }
    else {
        Node* current = *bucket;
        while (current->next != NULL && current->next->value < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 清空桶並返回排序結果
void collectBucket(Node** bucket) {
    for (int i = 0; i < 10; i++) {
        Node* current = bucket[i];
        while (current != NULL) {
            printf("[%.2f] ", current->value);
            current = current->next;
        }
    }
}

// 列出桶中內容
void printBuckets(Node** buckets, int bucketCount) {
    for (int i = 0; i < bucketCount; i++) {
        printf("Bucket[%d]: ", i);
        Node* current = buckets[i];
        while (current != NULL) {
            printf("[%.2f] ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

// Bucket-Sort 主函數
void bucketSort(float* arr, int n) {
    Node** buckets = (Node**)calloc(10, sizeof(Node*));  // 創建10個桶

    // 將數字分配到對應的桶中
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(10 * arr[i]);
        if (bucketIndex >= 10) bucketIndex = 10 - 1;
        insertNode(&buckets[bucketIndex], arr[i]);
    }

    // 列出所有桶的內容
    printf("分配到桶中後的結果:\n");
    printBuckets(buckets, 10);

    //// 從桶中取回排序結果
    //int index = 0;
    //for (int i = 0; i < 10; i++) {
    printf("\n");
    printf("\n");
        collectBucket(buckets);
    //}

    free(buckets);
}

// 主程式
int main() {
    FILE* file = fopen("1000.txt", "r");
    if (file == NULL) {
        printf("無法打開檔案！\n");
        return 1;
    }

    float arr[MAX_SIZE];
    int n = 0;

    // 從檔案中讀取數字
    while (fscanf(file, "%f", &arr[n]) != EOF && n < MAX_SIZE) {
        n++;
    }
    fclose(file);

    // 排序
    bucketSort(arr, n);

    //// 輸出結果
    //printf("排序後的數字:\n");
    //for (int i = 0; i < n; i++) {
    //    printf("%.2f ", arr[i]);
    //}
    //printf("\n");

    return 0;
}
