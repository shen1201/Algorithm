#include<stdio.h>


int fun2(int A[], int left, int  mid, int right, int* crosssS, int* crosssE) {
    int leftSum = -100000;
    int sum = 0;
    int tempstart = mid;

    for (int i = mid; i >= left; i--)
    {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            tempstart = i;
        }
    }

    int rightSum = -100000;
    sum = 0;
    int tempend = mid;

    for (int i = mid+1; i <= right; i++)
    {
        sum += A[i];

        if (sum > rightSum) {
            rightSum = sum;
            tempend = i;
        }
    }


    *crosssS = tempstart;
    *crosssE = tempend;
    return rightSum + leftSum;
}

int maxSubArray(int A[], int left, int right, int* start, int* end) {
    if (left == right) {
        *start = left;
        *end = right;
        return A[left];
    }

    int mid = (left + right) / 2;

    int leftS, leftE;
    int rightS, rightE;
    int crosssS, crosssE;

    int maxleftsum = maxSubArray(A, left, mid, &leftS, &leftE);
    int maxrightsum = maxSubArray(A, mid+1, right, &rightS, &rightE);

    int maxcross = fun2(A, left, mid, right, &crosssS, &crosssE);

    if (maxleftsum >= maxrightsum && maxleftsum >= maxcross) {
        *start = leftS;
        *end = leftE;
        return maxleftsum;
    }
    else if (maxrightsum >= maxleftsum && maxrightsum >= maxcross) {
        *start = rightS;
        *end = rightE;
        return maxrightsum;
    }
    else {
        *start = crosssS;
        *end = crosssE;
        return maxcross;
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

    while(fscanf(file,"%d",&arr[n])!=EOF){
        n++;
    }
    fclose(file);

    int start, end;

    int maxsum = maxSubArray(arr, 0, n - 1, &start, &end);

    printf("%d \n", maxsum);

    for (int i = start; i <= end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
	return 0;
}