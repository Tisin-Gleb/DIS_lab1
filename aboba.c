#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/time.h>
int N = 1000; // клч элементов в массиве.

void merge(uint32_t arr[], int left, int mid, int right) // =========MERGE==========
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	uint32_t L[n1], R[n2];

	for (i = 0; i < n1; i++){
		L[i] = arr[left + i];
    }
	for (j = 0; j < n2; j++){
		R[j] = arr[mid + 1 + j];
    }
	
	i = 0; 
	j = 0; 
	k = left; 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(uint32_t arr[], int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void counting_sort(uint32_t *arr, int border) // =============COUNTING_SORT================
{  
    int max_element = arr[0];
    for (int i = 0; i < border - 1; i++){
        if (arr[i] < arr[i+1]){
            max_element = arr[i+1];
        }
    }
    int* counts = (int*)malloc((max_element+1) * sizeof(*arr));
    memset(counts, 0, sizeof(*arr)*(max_element+1)); //массив заполнил нулями

    for(int i = 0; i < border; i++){
        counts[arr[i]]++;
    }

    for(int i = 0, current_position = 0; i < max_element+1; i++){
        for (int j = 0; j < counts[i]; j++){
            arr[current_position] = i;
            current_position++;
        }
    }
}

void insertion_sort(int n, uint32_t arr[]) // ===============INSERTION_SORT=================
{
    int key;
    int j;

    for (int i = 2; i < n; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1; 
        }
        arr[j + 1] = key;
    }
}

void printArray(uint32_t A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
	uint32_t *arr;
	uint32_t a[N];
	double start, end;

    puts("Выберите сортировку(1.Merge 2.Insertion. 3.Counting)");
	int sort_type;
	scanf("%d", &sort_type);
    switch (sort_type)
	{
	case 1:
		
		for (int i = 0; i < N; i++){
			a[i] = getrand(0, 166000);
		}
		int low = 0;
		int high = sizeof(a)/sizeof(a[0]);
		start = wtime();
		merge_sort(a, low, high-1);
		printArray(a, N);
		end = wtime();
		printf("Время на Mergesort %f\n", end-start);
		break;
	case 2:
		arr = (uint32_t*)malloc(N * sizeof(uint32_t));
		for (int i = 0; i < N; i++){
			arr[i] = getrand(0, 166000);
		}
		start = wtime();
		insertion_sort(N, arr);
		//printArray(arr, N);
		end = wtime();
		printf("Время на Insertionsort %f\n", end-start);
		break;
	case 3:
		arr = (uint32_t*)malloc(N * sizeof(uint32_t));
		for (int i = 0; i < N; i++){
			arr[i] = getrand(0, 166000);
		}
		start = wtime();
		counting_sort(arr, N);
		//printArray(arr, N);
		end = wtime();
		printf("Время на Countingsort %f\n", end-start);
		break;
	default:
		break;
	}
    return 0;
}
