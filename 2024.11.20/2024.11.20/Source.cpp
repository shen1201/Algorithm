#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000  // ���]�̦h�� 1000 ���ƾ�

// �w�q�@�Ӹ`�I���c�H�B�z�����h�ӼƦr
typedef struct Node {
    float value;
    struct Node* next;
} Node;

// �Ыؤ@�Ӹ`�I
Node* createNode(float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// ���J�Ʀr����]���J�ƧǥH�O���ƧǪ��A�^
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

// �M�ű�ê�^�Ƨǵ��G
void collectBucket(Node** bucket) {
    for (int i = 0; i < 10; i++) {
        Node* current = bucket[i];
        while (current != NULL) {
            printf("[%.2f] ", current->value);
            current = current->next;
        }
    }
}

// �C�X�����e
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

// Bucket-Sort �D���
void bucketSort(float* arr, int n) {
    Node** buckets = (Node**)calloc(10, sizeof(Node*));  // �Ы�10�ӱ�

    // �N�Ʀr���t���������
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(10 * arr[i]);
        if (bucketIndex >= 10) bucketIndex = 10 - 1;
        insertNode(&buckets[bucketIndex], arr[i]);
    }

    // �C�X�Ҧ������e
    printf("���t����᪺���G:\n");
    printBuckets(buckets, 10);

    //// �q�����^�Ƨǵ��G
    //int index = 0;
    //for (int i = 0; i < 10; i++) {
    printf("\n");
    printf("\n");
        collectBucket(buckets);
    //}

    free(buckets);
}

// �D�{��
int main() {
    FILE* file = fopen("1000.txt", "r");
    if (file == NULL) {
        printf("�L�k���}�ɮסI\n");
        return 1;
    }

    float arr[MAX_SIZE];
    int n = 0;

    // �q�ɮפ�Ū���Ʀr
    while (fscanf(file, "%f", &arr[n]) != EOF && n < MAX_SIZE) {
        n++;
    }
    fclose(file);

    // �Ƨ�
    bucketSort(arr, n);

    //// ��X���G
    //printf("�Ƨǫ᪺�Ʀr:\n");
    //for (int i = 0; i < n; i++) {
    //    printf("%.2f ", arr[i]);
    //}
    //printf("\n");

    return 0;
}
