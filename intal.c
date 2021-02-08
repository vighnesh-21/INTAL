#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

static void strip(char **s) {
	int n = strlen(*s);
	int count = 0;
	for (int i = 0; (*s)[i] == '0'; ++i) {
		++count;
	}
	if (count == n) {
		free(*s);
		*s = malloc(sizeof(char) * 2);
		(*s)[0] = '0';
		(*s)[1] = '\0';
	} else {
		for (int i = 0; i <= (n - count); ++i) {
			(*s)[i] = (*s)[i + count];
		}
	}
}

char* intal_add(const char* intal1,const char* intal2) {
	int i1,i2;
	i1 = strlen(intal1);
	i2 = strlen(intal2);
	int sum, carry = 0;
	char *result;
	if (i1 <= i2) {
		result = malloc(sizeof(char) * (i2 + 2));
		for (int i = 0; i < i1; ++i) {
			sum = intal2[i2 - i - 1] + intal1[i1 - i - 1] - '0' - '0' + carry;
			carry = sum/10;
			result[i2 - i - 1] = sum%10 + '0';
		}
		for (int i = 0; i < (i2 - i1); ++i) {
			sum = intal2[i2 - (i1 + i + 1)] - '0' + carry; 
			carry = sum/10;
			result[i2 - (i1 + i + 1)] = sum%10 + '0';
		}
		result[i2] = '\0';
		if (carry != 0) {
			for (int i = i2; i >= 0; --i) {
				result[i + 1] = result[i];
			}
			result[0] = carry + '0';
		}

		strip(&result);
		return result;
	} else {
		result = malloc(sizeof(char) * (i1 + 2));
		for (int i = 0; i < i2; ++i) {
			sum =  intal1[i1 - i - 1] + intal2[i2 - i - 1] - '0' - '0' + carry;
			carry = sum/10;
			result[i1 - i - 1] = sum%10 + '0';
		}
		for (int i = 0; i < (i1 - i2); ++i) {
			sum = intal1[i1 - (i2 + i + 1)] - '0' + carry; 
			carry = sum/10;
			result[i1 - (i2 + i + 1)] = sum%10 + '0';
		}
		result[i1] = '\0';
		if (carry != 0) {
			for (int i = i1; i >= 0; --i) {
				result[i + 1] = result[i];
			}
			result[0] = carry + '0';
		}
		strip(&result);
		return result;
	} 
}

int intal_compare(const char* intal1,const char* intal2) {
	int i1,i2;
	i1 = strlen(intal1);
	i2 = strlen(intal2);
	if (i1 > i2) {
		return 1;
	} else if (i1 < i2) {
		return -1;
	} else { 
		for (int i = 0; i < i1; ++i) {
			if (intal1[i] < intal2[i]) {
				return -1;
			} else if (intal1[i] > intal2[i]) {
				return 1;
			}
		}
		return 0;
	}
}

char* intal_diff(const char* int1,const char* int2) {
	int compValue = intal_compare(int1, int2);
	int i1,i2;
	i1 = strlen(int1);
	i2 = strlen(int2);
	int diff = 0;
	char *result;
	char *intal1 = malloc(sizeof(char) * (i1 + 1));
	char *intal2 = malloc(sizeof(char) * (i2 + 1));
	strcpy(intal1, int1);
	strcpy(intal2, int2);
	if (compValue == 0) {
		result = malloc(sizeof(char) * 2);
		result[0] = '0';
		result[1] = '\0';
		return result;
	} else if (compValue == -1) {
		result = malloc(sizeof(char) * (i2 + 2));
		for (int i = 0; i < i1; ++i) {
			diff = (intal2[i2 - i - 1] - '0') - (intal1[i1 - i - 1] - '0');
			if (diff < 0) {
				diff += 10;
				if (intal2[i2 - i - 2] == '0') {
					int k = 0;
					while (intal2[i2 - i - 2 - k] == '0') {
						intal2[i2 - i - 2 - k] = '9';
						k++;
					}
					intal2[i2 - i - 2 - k] = ((intal2[i2 - i - 2 - k] - '0') - 1) + '0';
				} else {
					intal2[i2 - i - 2] = ((intal2[i2 - i - 2] - '0') - 1) + '0';
				}
			} 
			result[i2 - i - 1] = diff + '0';

		}
		for (int i = 0; i < (i2 - i1); ++i) {
			result[i2 - (i1 + i + 1)] = intal2[i2 - (i1 + 1 + i)];
		}
		result[i2] = '\0';
		int count = 0;
		for (int i = 0; result[i] == '0'; ++i) {
			++count;
		}
		for (int i = 0; i <= (i2 - count); ++i) {
			result[i] = result[i + count];
		}
		free(intal1);
		free(intal2);
		return result;
	} else {
		result = malloc(sizeof(char) * (i1 + 2));
		for (int i = 0; i < i2; ++i) {
			diff = (intal1[i1 - i - 1] - '0') - (intal2[i2 - i - 1] - '0');
			if (diff < 0) {
				diff += 10;
				if (intal1[i1 - i - 2] == '0') {
					int k = 0;
					while (intal1[i1 - i - 2 - k] == '0') {
						intal1[i1 - i - 2 - k] = '9';
						k++;
					}
					intal1[i1 - i - 2 - k] = ((intal1[i1 - i - 2 - k] - '0') - 1) + '0';
				} else {
					intal1[i1 - i - 2] = ((intal1[i1 - i - 2] - '0') - 1) + '0';
				}
			} 
			result[i1 - i - 1] = diff + '0';

		}
		for (int i = 0; i < (i1 - i2); ++i) {
			result[i1 - (i2 + i + 1)] = intal1[i1 - (i2 + 1 + i)];
		}
		result[i1] = '\0';
		int count = 0;
		for (int i = 0; result[i] == '0'; ++i) {
			++count;
		}
		for (int i = 0; i <= (i1 - count); ++i) {
			result[i] = result[i + count];
		}
		free(intal1);
		free(intal2);
		return result;
	}
}

static char *convertToIntal(int n) {
	if (n == 0) {
		char *result = malloc(sizeof(char) * 2);
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	int n1 = n;
	int count = 0;
	while (n >= 1) {
		n = n / 10;
		++count;
	}
	n = n1;
	char *result = malloc(sizeof(char) * (count + 1));
	for (int i = 0; i < count; ++i) {
		result[count - i - 1] = n%10 + '0';
		n = n / 10;
	}
	result[count] = '\0';
	strip(&result);
	return result;
}
//Character swap
static void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}
//Reversing a string
static char* strrev(const char * str) 
{ 
	int n = strlen(str); 
	char *rev = malloc(sizeof(char) * (n + 1));
	strcpy(rev, str); 
    for (int i=0, j=n-1; i<j; i++,j--) 
		swap(&rev[i], &rev[j]);        
	return rev; 
} 


char* intal_multiply(const char* int1,const char* int2) {
	int i1, i2, temp;
	i1 = strlen(int1);
	i2 = strlen(int2);
	char *result = malloc(sizeof(char) * (i1 + i2 + 1));
	for (int c = 0; c <= i1 + i2; ++c) {
		result[c] = '0';
	}
	char *intal1 = strrev(int1);
	char *intal2 = strrev(int2);
	if (i1 < i2) {
		int tempnum1;
		char *tempnum2;
		tempnum1 = i1;
		i1 = i2;
		i2 = tempnum1;
		tempnum2 = intal1;
		intal1 = intal2;
		intal2 = tempnum2;
	}
		int count = 0;
		int i = 0;
		int j = 0;
		while (i < i2) {
			int carry = 0;
			j = 0;
			while (j < i1) {
				temp = ((result[j + count] - '0') + (intal2[i] - '0')*(intal1[j] - '0') + carry);
				carry = temp / 10;
				result[j + count] = (temp % 10) + '0';
				++j;
			}
			temp = ((result[j + count] - '0') + carry);
			carry = temp/10;
			result[j + count] = (temp%10) + '0';
			++j;
			if (carry != 0) {
				result[j + count] = carry + '0';
			}
			++i;
			++count;
		}
		result[j + count - 1] = '\0';
		char *temp1 = result;
		result = strrev(result);
		strip(&result);
		free(temp1);
		
		free(intal1);
		free(intal2);
		return result;

}
char* intal_pow(const char* intal1, unsigned int n);
char* intal_mod(const char* intal1,const char* intal2) {
	int res = intal_compare(intal1, intal2);
	char *zero = convertToIntal(0);
	int i1, i2;
	i1 = strlen(intal1);
	i2 = strlen(intal2);
	char *int1 = malloc(sizeof(char) * (i1 + 1));
	char *int2 = malloc(sizeof(char) * (i2 + 1));
	strcpy(int1, intal1);
	strcpy(int2, intal2);
	if (res == 1) {
		char *ten = convertToIntal(10);
		char *temp;
		while (i1 > i2) {
			if (i1 - i2 >= 1) {
				int2 = intal_multiply(int2, intal_pow(ten, i1 - 1 - (i2 - 1) - 1));
			}
			while ((intal_compare(int1, int2) == 1) || (intal_compare(int1, int2) == 0)) {
				temp = int1;
				int1 = intal_diff(int1, int2);
				free(temp);
			}
			i1 = strlen(int1);	
			free(int2);
			int2 = malloc(sizeof(char) * (i2 + 1));
			strcpy(int2, intal2);
			// i2 = strlen(int2);
		}
		if (intal_compare(int1, int2) == 1) {
			while (intal_compare(int1, int2) == 1) {
				temp = int1;
				int1 = intal_diff(int1,int2);
				free(temp);
			}
		}
		if (intal_compare(int1, int2) == 0) {
			free(int1);
			free(int2);
			return zero;
		} else {
			free(int2);
			free(zero);
			strip(&int1);
			return int1;
		}
	} else if (res == -1){
		free(zero);
		strip(&int1);
		free(int2);
		return int1;
	} else {
		free(int1);
		free(int2);
		return zero;
	}
}

char* intal_pow(const char* intal1, unsigned int n) {
	char zero[2] = {'0', '\0'};
	if (!strcmp(intal1, zero)) {
		char *result = malloc(sizeof(char) * 2);
		result[0] = '0';
		result[1] = '\0';
		return result;
	} else if (n == 0) {
		char *result = malloc(sizeof(char) * 2);
		result[0] = '1';
		result[1] = '\0';
		return result;
	} else {
		int n1 = n;
		n = n/2;
		char *temp;
		char *resprev = intal_pow(intal1, n);
		char *result = intal_multiply(resprev, resprev);
		if (n1%2 == 1) {
			temp = result;
			result = intal_multiply(result, intal1);
			free(temp);
		}
		free(resprev);
		strip(&result);
		return result;

	}
}

char* intal_fibonacci(unsigned int n) {
	char *prev = malloc(sizeof(char) * 2);
	char *curr = malloc(sizeof(char) * 2);
	prev[0] = '0';
	curr[0] = '1';
	prev[1] = curr[1] = '\0';
	if (n == 0) {
		return prev;
	} else if (n == 1) {
		return curr;
	}
	char *temp;
	for (int i = 2; i <= n; ++i) {
		temp = curr;
		curr = intal_add(curr, prev);
		free(temp);
		temp = prev;
		prev = intal_diff(curr, prev);
		free(temp);
	}
	free(prev);
	strip(&curr);
	return curr;
}

char* intal_gcd(const char* a,const char* b) {
	if (!intal_compare(a, "0")) {
		char *temp = malloc(sizeof(char) * (strlen(b) + 1));
		strcpy(temp,b);
		return temp;
	} else {
		return intal_gcd(intal_mod(b,a), a);
	}
}

char* intal_factorial(unsigned int n) {
	char *temp = malloc(sizeof(char) * 2);
	char *result = malloc(sizeof(char) * 2);
	char *freepointer;
	result[0] = '1';
	result[1] = '\0';
	temp[0] = '1';
	temp[1] = '\0';
	char one[] = {'1', '\0'};
	for (int i = 2; i <= n; ++i) {
		freepointer = temp;
		temp = intal_add(freepointer, one);
		free(freepointer);
		freepointer = result;
		result = intal_multiply(freepointer, temp);
		free(freepointer);
	}
	free(temp);
	strip(&result);
	return result;
}

static int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

char* intal_bincoeff(unsigned int n, unsigned int k) {
	char *one = malloc(sizeof(char) * 2);
	char *zero = malloc(sizeof(char) * 2);
	one[0] = '1';
	zero[0] = '0';
	one[1] = zero[1] = '\0';
	if ((k == 0) || (k == n)){
		return one;
	} else {
		int k1 = k;
		int n1 = n;
		if (k1 > n1/2) {
			k1 = n1 - k1;
		}
		char **arr = malloc(sizeof(char *) * (k1 + 1));
		for (int i = 1; i < (k1 + 1); ++i) {
			arr[i] = convertToIntal(0);
		}
		arr[0] = convertToIntal(1);
		for (int i = 1; i <= n1; ++i) {
			if (i >= k1) {
				for (int j = 0; j <= k1; ++j) {
					if (((k1 - j) == i) || ((k1 - j) == 0)) {
						free(arr[k1 - j]);
						arr[k1 - j] = convertToIntal(1);
					} else {
						char *temp = arr[k1 - j];
						arr[k1 - j] = intal_add(arr[k1 - j], arr[k1-j - 1]);
						free(temp);
					}
				}
			} else {
				for (int j = i; j >= 0; --j) {
					if ((j == i) || (j == 0)) {
						free(arr[j]);
						arr[j] = convertToIntal(1);
					} else {
						char *temp = arr[j];
						arr[j] = intal_add(arr[j], arr[j - 1]);
						free(temp);
					}

				}
			}
		}
		int rn = strlen(arr[k1]);
		char *result = malloc(sizeof(char) * (rn + 1));
		strcpy(result, arr[k1]);
		for (int i = 0; i <= k1; ++i) {
			free(arr[i]);
		}
		free(arr);
		return result;
	}
}

int intal_max(char **arr, int n) {
	char *max = convertToIntal(0);
	int count = 0;
	for (int i = 0; i < n; ++i) {
		if (intal_compare(max, arr[i]) == -1) {
			free(max);
			count = i;
			max = malloc(sizeof(char) * (strlen(arr[i]) + 1));
			strcpy(max, arr[i]);
		}
	}
	free(max);
	return count;
}

int intal_min(char **arr, int n) {
	char *min = malloc(sizeof(char) * (strlen(arr[0]) + 1));
	int count = 0;
	strcpy(min, arr[0]);
	for (int i = 1; i < n; ++i) {
		if (intal_compare(min, arr[i]) == 1) {
			free(min);
			count = i;
			min = malloc(sizeof(char) * (strlen(arr[i]) + 1));
			strcpy(min, arr[i]);
		}
	}
	free(min);
	return count;
}

int intal_search(char **arr, int n,const char* key) {
	int i = 0;
	while (i < n) {
		if (!intal_compare(arr[i], key)) {
			return i;
		}
		++i;
	}
	return -1;
}

int intal_binsearch(char **arr, int n, const char* key) {
	int start = 0;
	int end = n - 1;
	while (start <= end) {
		int mid = (start + end) / 2;
		int num = intal_compare(key, arr[mid]);
		if (num == 0) {
			int k = 0;
			if ((mid >= 1) && (intal_compare(arr[mid - 1], key) == 0)) {
				while (((mid - k) >= 0) && (intal_compare(arr[mid - k], key) == 0)) {
					k = k + 1;
				}
				return (mid - k + 1);
			} else {
				return mid;
			}
		} else if (num == -1) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}
	return -1;
}

static void heapify(char **arr, int i, int n) {
	if (2*i > n) {
		return;
	}
	int j = 2*i;
	if ((j + 1) <= n) {
		if (intal_compare(arr[j], arr[j - 1]) == 1) {
			j = j + 1;
		}
	}
	if (intal_compare(arr[j - 1], arr[i - 1]) == 1) {
		char *temp = arr[j - 1];
		arr[j - 1] = arr[i - 1];
		arr[i - 1] = temp;
		heapify(arr, j, n);
	}
}

void intal_sort(char **arr, int n) {
	for (int i = n/2; i >= 1; --i) {
		heapify(arr, i, n);
	}
	for (int i = n; i > 1; --i) {
		char *temp = arr[i - 1];
		arr[i - 1] = arr[0];
		arr[0] = temp;
		heapify(arr, 1, i - 1);
	}
}

char* coin_row_problem(char **arr, int n) {
	char *zero = malloc(sizeof(char) * 2);
	zero[0] = '0';
	zero[1] = '\0';
	char *temp;
	char *a1 = convertToIntal(0);
	char *a2 = malloc(sizeof(char) * (strlen(arr[0]) + 1));
	strcpy(a2, arr[0]);
	char *sum;
	for (int i = 2; i <= n; ++i) {
		sum = intal_add(arr[i - 1], a1);
		if (intal_compare(sum, a2) == 1) {
			temp = a1;
			a1 = a2;
			a2 = sum;
			free(temp);
		} else {
			free(a1);
			a1 = a2;
			a2 = intal_add(a2, zero);
			free(sum);
		}
	}
	free(zero);
	free(a1);
	strip(&a2);
	return a2;
}
