#include <stdio.h>
#include <limits.h>

// ����V�������̤j�l�}�C�M�A�ê�^�l�}�C���d��
int maxCrossingSubArray(int A[], int left, int mid, int right, int* crossStart, int* crossEnd) {
    int leftSum = INT_MIN;
    int sum = 0;
    int tempStart = mid;

    // �q�����I�V���M���A�p��l�}�C�M
    for (int i = mid; i >= left; i--) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            tempStart = i; // ��s����l�}�C���}�l��m
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int tempEnd = mid;

    // �q�����I���k��@��}�l�V�k�M���A�p��l�}�C�M
    for (int i = mid + 1; i <= right; i++) {
        sum += A[i];
        if (sum > rightSum) {
            rightSum = sum;
            tempEnd = i; // ��s�k��l�}�C��������m
        }
    }

    *crossStart = tempStart;
    *crossEnd = tempEnd;
    return leftSum + rightSum;
}

// ���v�k�G���j�a��X�̤j�l�}�C�M�A�ê�^�l�}�C���d��
int maxSubArray(int A[], int left, int right, int* start, int* end) {
    if (left == right) {
        *start = left;
        *end = right;
        return A[left];
    }

    int mid = (left + right) / 2;

    int leftStart, leftEnd;
    int rightStart, rightEnd;
    int crossStart, crossEnd;

    // ���j�D�ѥ��b�������̤j�l�}�C�M
    int maxLeftSum = maxSubArray(A, left, mid, &leftStart, &leftEnd);

    // ���j�D�ѥk�b�������̤j�l�}�C�M
    int maxRightSum = maxSubArray(A, mid + 1, right, &rightStart, &rightEnd);

    // �p���V�������̤j�l�}�C�M
    int maxCrossingSum = maxCrossingSubArray(A, left, mid, right, &crossStart, &crossEnd);

    // ��^�T�̤����̤j�ȡA�ç�s�_�l�M��������
    if (maxLeftSum >= maxRightSum && maxLeftSum >= maxCrossingSum) {
        *start = leftStart;
        *end = leftEnd;
        return maxLeftSum;
    }
    else if (maxRightSum >= maxLeftSum && maxRightSum >= maxCrossingSum) {
        *start = rightStart;
        *end = rightEnd;
        return maxRightSum;
    }
    else {
        *start = crossStart;
        *end = crossEnd;
        return maxCrossingSum;
    }
}

int main() {
    FILE* file;
    int arr[100], n = 0;

    // ���}�ɮר�Ū���ƾ�
    file = fopen("01.txt", "r");
    if (file == NULL) {
        printf("�L�k���}�ɮ�\n");
        return 1;
    }

    // �q�ɮ�Ū���}�C�ƾ�
    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(file);

    // ��l���ܼ�
    int start, end;

    // �I�s maxSubArray ��ơA�D�Ѱ}�C�����̤j�l�}�C�M
    int maxSum = maxSubArray(arr, 0, n - 1, &start, &end);

    // ��X�̤j�l�}�C�M�H�Τl�}�C���d��
    printf("�̤j�l�}�C�M��: %d\n", maxSum);
    printf("�̤j�l�}�C��: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
