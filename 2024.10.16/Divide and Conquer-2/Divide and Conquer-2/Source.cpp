#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 20

// 矩陣相加函數
// 將矩陣 A 和 B 相加，結果儲存在矩陣 C 中
void matrix_add(int n, int A[size][size], int B[size][size], int C[size][size]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j]; // 元素逐一相加
        }
    }
}

// 矩陣相減函數
// 將矩陣 A 和 B 相減，結果儲存在矩陣 C 中
void matrix_subtract(int n, int A[size][size], int B[size][size], int C[size][size]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j]; // 元素逐一相減
        }
    }
}

// 使用 Strassen 算法進行矩陣乘法
// 將矩陣 A 和 B 相乘，結果儲存在矩陣 C 中
void strassen_matrix_multiply(int n, int A[size][size], int B[size][size], int C[size][size]) {
    // 基本情況：當矩陣大小為 1x1 時，直接相乘
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    else {
        int mid = n / 2;  // 將矩陣劃分為 2x2 的子矩陣

        // 分配子矩陣
        int A11[size][size], A12[size][size], A21[size][size], A22[size][size];
        int B11[size][size], B12[size][size], B21[size][size], B22[size][size];
        int C11[size][size], C12[size][size], C21[size][size], C22[size][size];
        int M1[size][size], M2[size][size], M3[size][size], M4[size][size], M5[size][size], M6[size][size], M7[size][size];
        int temp1[size][size], temp2[size][size];  // 用於中間結果的矩陣

        // 初始化結果矩陣 C 的子矩陣為 0
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C11[i][j] = 0;
                C12[i][j] = 0;
                C21[i][j] = 0;
                C22[i][j] = 0;
            }
        }

        // 將矩陣 A 和 B 分解為四個子矩陣
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + mid];
                A21[i][j] = A[i + mid][j];
                A22[i][j] = A[i + mid][j + mid];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + mid];
                B21[i][j] = B[i + mid][j];
                B22[i][j] = B[i + mid][j + mid];
            }
        }

        // 計算 Strassen 算法的 7 個乘積 M
        matrix_add(mid, A11, A22, temp1); // temp1 = A11 + A22  
        matrix_add(mid, B11, B22, temp2); // temp2 = B11 + B22
        strassen_matrix_multiply(mid, temp1, temp2, M1); // M1 = (A11 + A22) * (B11 + B22)

        matrix_add(mid, A21, A22, temp1); // temp1 = A21 + A22
        strassen_matrix_multiply(mid, temp1, B11, M2); // M2 = (A21 + A22) * B11

        matrix_subtract(mid, B12, B22, temp1); // temp1 = B12 - B22
        strassen_matrix_multiply(mid, A11, temp1, M3); // M3 = A11 * (B12 - B22)

        matrix_subtract(mid, B21, B11, temp1); // temp1 = B21 - B11
        strassen_matrix_multiply(mid, A22, temp1, M4); // M4 = A22 * (B21 - B11)

        matrix_add(mid, A11, A12, temp1); // temp1 = A11 + A12
        strassen_matrix_multiply(mid, temp1, B22, M5); // M5 = (A11 + A12) * B22

        matrix_subtract(mid, A21, A11, temp1); // temp1 = A21 - A11
        matrix_add(mid, B11, B12, temp2); // temp2 = B11 + B12
        strassen_matrix_multiply(mid, temp1, temp2, M6); // M6 = (A21 - A11) * (B11 + B12)

        matrix_subtract(mid, A12, A22, temp1); // temp1 = A12 - A22
        matrix_add(mid, B21, B22, temp2); // temp2 = B21 + B22
        strassen_matrix_multiply(mid, temp1, temp2, M7); // M7 = (A12 - A22) * (B21 + B22)

        // 計算子矩陣 C
        matrix_add(mid, M1, M4, temp1);
        matrix_subtract(mid, temp1, M5, temp2);
        matrix_add(mid, temp2, M7, C11); // C11 = M1 + M4 - M5 + M7

        matrix_add(mid, M3, M5, C12); // C12 = M3 + M5
        matrix_add(mid, M2, M4, C21); // C21 = M2 + M4

        matrix_add(mid, M1, M3, temp1);
        matrix_subtract(mid, temp1, M2, temp2);
        matrix_add(mid, temp2, M6, C22); // C22 = M1 + M3 - M2 + M6

        // 將子矩陣合併到結果矩陣 C 中
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C[i][j] = C11[i][j];
                C[i][j + mid] = C12[i][j];
                C[i + mid][j] = C21[i][j];
                C[i + mid][j + mid] = C22[i][j];
            }
        }
    }
}

int main() {
    FILE* fileA = fopen("1A.txt", "r");
    FILE* fileB = fopen("1B.txt", "r");
    if (fileA == NULL || fileB == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int n;
    fscanf(fileA, "%d %d", &n, &n);
    fscanf(fileB, "%d %d", &n, &n);

    int A[size][size];
    int B[size][size];
    int C[size][size];

    // 讀取矩陣 A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fileA, "%d", &A[i][j]);
        }
    }

    // 讀取矩陣 B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fileB, "%d", &B[i][j]);
        }
    }

    fclose(fileA);
    fclose(fileB);

    // 初始化矩陣 C
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }

    // 計算執行時間
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // 執行 Strassen 矩陣乘法
    strassen_matrix_multiply(n, A, B, C);

    

    // 打印結果
    printf("結果矩陣 C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    //for (int i = 0; i < 40000; i++)
    //{
    //    // 執行 Strassen 矩陣乘法
    //    strassen_matrix_multiply(n, A, B, C);
    //}

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // 打印執行時間
    printf("\n執行時間: %f 秒\n", cpu_time_used);

    return 0;
}