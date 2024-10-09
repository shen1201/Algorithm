#include <stdio.h>
#include <limits.h>

// 找到跨越中間的最大子陣列和，並返回子陣列的範圍
int maxCrossingSubArray(int A[], int left, int mid, int right, int* crossStart, int* crossEnd) {
    int leftSum = INT_MIN;
    int sum = 0;
    int tempStart = mid;

    // 從中間點向左遍歷，計算子陣列和
    for (int i = mid; i >= left; i--) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            tempStart = i; // 更新左邊子陣列的開始位置
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int tempEnd = mid;

    // 從中間點的右邊一位開始向右遍歷，計算子陣列和
    for (int i = mid + 1; i <= right; i++) {
        sum += A[i];
        if (sum > rightSum) {
            rightSum = sum;
            tempEnd = i; // 更新右邊子陣列的結束位置
        }
    }

    *crossStart = tempStart;
    *crossEnd = tempEnd;
    return leftSum + rightSum;
}

// 分治法：遞迴地找出最大子陣列和，並返回子陣列的範圍
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

    // 遞迴求解左半部分的最大子陣列和
    int maxLeftSum = maxSubArray(A, left, mid, &leftStart, &leftEnd);

    // 遞迴求解右半部分的最大子陣列和
    int maxRightSum = maxSubArray(A, mid + 1, right, &rightStart, &rightEnd);

    // 計算跨越中間的最大子陣列和
    int maxCrossingSum = maxCrossingSubArray(A, left, mid, right, &crossStart, &crossEnd);

    // 返回三者中的最大值，並更新起始和結束索引
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

    // 打開檔案並讀取數據
    file = fopen("01.txt", "r");
    if (file == NULL) {
        printf("無法打開檔案\n");
        return 1;
    }

    // 從檔案讀取陣列數據
    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(file);

    // 初始化變數
    int start, end;

    // 呼叫 maxSubArray 函數，求解陣列中的最大子陣列和
    int maxSum = maxSubArray(arr, 0, n - 1, &start, &end);

    // 輸出最大子陣列和以及子陣列的範圍
    printf("最大子陣列和為: %d\n", maxSum);
    printf("最大子陣列為: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
