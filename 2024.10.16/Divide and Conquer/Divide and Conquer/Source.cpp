#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 8

// 矩陣相加
void matrix_add(int n, int A[size][size], int B[size][size], int C[size][size]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// 矩陣遞歸乘法
void square_matrix_multiply_recursive(int n, int A[size][size], int B[size][size], int C[size][size]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    else {
        int mid = n / 2;

        // 分配子矩陣
        int A11[size][size], A12[size][size], A21[size][size], A22[size][size];
        int B11[size][size], B12[size][size], B21[size][size], B22[size][size];
        int C11[size][size], C12[size][size], C21[size][size], C22[size][size];

        // 初始化結果矩陣為0
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C11[i][j] = 0;
                C12[i][j] = 0;
                C21[i][j] = 0;
                C22[i][j] = 0;
            }
        }

        // 將矩陣 A 和 B 分解為 4 個子矩陣
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

        // 計算四個部分的乘積 C
        int temp1[size][size], temp2[size][size];
        square_matrix_multiply_recursive(mid, A11, B11, temp1);
        square_matrix_multiply_recursive(mid, A12, B21, temp2);
        matrix_add(mid, temp1, temp2, C11);

        square_matrix_multiply_recursive(mid, A11, B12, temp1);
        square_matrix_multiply_recursive(mid, A12, B22, temp2);
        matrix_add(mid, temp1, temp2, C12);

        square_matrix_multiply_recursive(mid, A21, B11, temp1);
        square_matrix_multiply_recursive(mid, A22, B21, temp2);
        matrix_add(mid, temp1, temp2, C21);

        square_matrix_multiply_recursive(mid, A21, B12, temp1);
        square_matrix_multiply_recursive(mid, A22, B22, temp2);
        matrix_add(mid, temp1, temp2, C22);

        // 合併子矩陣到最終結果矩陣 C
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

    // 進行矩陣乘法
    square_matrix_multiply_recursive(n, A, B, C);

    

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
    //    // 進行矩陣乘法
    //    square_matrix_multiply_recursive(n, A, B, C);

    //}


    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // 打印執行時間
    printf("\n執行時間: %f 秒\n", cpu_time_used);

    return 0;
}