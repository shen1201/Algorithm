#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void countsort(int arr[], int n, int exp, int base) {
	int output[2000] = {}; // 用來暫存排序後元素的輸出陣列
	int count[2000] = {}; // 用來存儲每個數字出現次數的陣列

	for (int i = 0; i < n; i++)
	{
		int index = (arr[i]>>exp) & (base - 1);
		count[index]++;
	}

	for (int i = 1; i < base; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = n-1; i >=0; i--)
	{
		int index = (arr[i] >> exp) & (base - 1);
		output[count[index] - 1] = arr[i];
		count[index]--;
	}

	for (int i = 0; i < n; i++)
	{
		arr[i] = output[i];
	}
}


void radix(int arr[100], int n, int r) {
	int base = 1 << r;

	for(int exp = 0; exp < 8 ; exp+=r)
	{
		countsort(arr, n, exp, base);
	}
}


int main() {
	FILE* fp = fopen("2_100.txt", "r");

	char line[20];
	int n=0;
	int arr[100];

	while (fgets(line, sizeof(line), fp) && n < 100) {
		arr[n++] = (int)strtol(line, NULL, 2);
	}

	fclose(fp);

	int r = 2;

	radix(arr, n, r);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 8-1; j >=0 ; j--)
		{
			printf("%d", (arr[i] >> j) & 1);
		}
		printf("\n");
	}
	
	return 0;
}