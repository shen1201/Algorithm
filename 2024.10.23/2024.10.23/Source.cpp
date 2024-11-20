#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void insertElement(int arr[], int* n, int value) {
    arr[*n] = value;
    (*n)++;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    FILE* file = fopen("1.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int arr[100];
    int n = 0;
    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(file);

    printf("Original array: \n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    int value;
    printf("Enter a value to insert: ");

    while(true){
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        else {
            insertElement(arr, &n, value);
            printf("Array after inserting %d: \n", value);
            printArray(arr, n);
        }
        
    }

    

    heapSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
