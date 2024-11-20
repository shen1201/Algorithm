#include<stdio.h>

int main() {
	int num1, num2, result, count = 0;
	for (int i = 0; i < 5; i++) {
		printf("input:");
		scanf("%d %d %d", &num1, &num2, &result);
		if (num1 > 0) {
			num1 = 1;
		}
		if (num2 > 0) {
			num2 = 1;
		}
		if ((num1 & num2) == result) {
			printf("AND\n");
			count++;
		}
		if ((num1 | num2) == result) {
			printf("OR\n");
			count++;
		}
		if ((num1 ^ num2) == result) {
			printf("XOR\n");
			count++;
		}
		if (count == 0) {
			printf("IMPOSSIBLE\n");
		}
		count = 0;
	}
	return 0;
}