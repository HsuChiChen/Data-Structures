#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <ctime>
#include<list>
#include<cmath>
using namespace std;

void insertion(int arr[], int n);
void selection(int arr[], int n);
void swap(int* array_1, int* array_2);
void quickSort(int arr[], int left, int right);
void mergeSort(int arr[],int l,int r);
void merge(int arr[], int l, int m, int r);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
//void radixSort(int *arr, int n, int max); 
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);

int main(){
	int arr[100000] = {0};
	int num = 10000;
	clock_t start, end;
	double cpu_time_used;
	unsigned seed;
	
	seed = (unsigned)time(NULL);
	srand(seed);
	
	do{
		cout << "count = " << num << endl;
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//insertion sort
		start = clock();
		insertion(arr, num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "Insert_sort time = " << cpu_time_used  << "(s)" << endl;
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//selection sort
		start = clock();
		selection(arr, num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "Select_sort time = " << cpu_time_used  << "(s)" << endl;
		
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//quick sort
		start = clock();
		quickSort(arr, 0, num-1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "quick_sort time  = " << cpu_time_used  << "(s)" << endl;
		
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//merge sort
		start = clock();
		mergeSort(arr, 0, num-1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "merge_sort time  = " << cpu_time_used  << "(s)" << endl;
		
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//heap sort
		start = clock();
		heapSort(arr, num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "heap_sort time   = " << cpu_time_used  << "(s)" << endl;
		
		//generate random number
		for(int i=0; i<num; i++){
			arr[i] = rand()%100;
		}
		//Radix sort
		start = clock();
		radixSort(arr, num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "Radix_sort time  = " << cpu_time_used  << "(s)" << endl;
	
		num = num + 10000;
		cout << "----------------------------------------" << endl;
	}while(num <= 100000);
	
	//cout << "test" << endl;
	return 0;
}

void insertion(int arr[], int n){
	int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void selection(int arr[], int n){
	int i , j , min ;
	 for ( i = 0 ; i < n - 1 ; i ++ ) {
		 min = i ;
		 for ( j = i + 1 ; j < n ; j ++ )
			 if ( arr [ min ] > arr [ j ])
				 min = j ;
		 swap ( arr [ i ], arr [ min ]);
	 }
}
void swap(int* array_1, int* array_2){
	int temp = 0;

	temp = *array_1;
	*array_1 = *array_2;
	*array_2 = temp;
}
void quickSort(int arr[], int left, int right) {	
   int temp;
	if (left < right)
	{
		int pivot = arr[left];//假設pivot在第一個的位置
		int l = left;
		int r = right + 1;
		
		while (1)
		{
			while (l < right && arr[++l] < pivot);//向右找小於pivot的數值的位置
			while (r > 0 && arr[--r] > pivot);//向左找大於pivot的數值的位置

			if (l >= r)//範圍內pivot右邊沒有比pivot小的數,反之亦然
			{
				break;
			}
		
			swap(arr[l], arr[r]);//比pivot大的數移到右邊，比pivot小的數換到左邊
		}

		swap(arr[left], arr[r]);//將pivot移到中間

		quickSort(arr, left, r - 1);//左子數列做遞迴
		quickSort(arr, r + 1, right);//右子數列做遞迴
	}
} 
void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
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
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}
void heapify(int *arr, int n, int i){
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && *(arr+l) > *(arr+largest))
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && *(arr + r) > *(arr + largest))
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
/* void radixSort(int *arr, int n, int max) {
   int i, j, m, p = 1, index, temp, count = 0;
   list<int> pocket[10];      //radix of decimal number is 10
   for(i = 0; i< max; i++) {
      m = pow(10, i+1);
      p = pow(10, i);
      for(j = 0; j<n; j++) {
         temp = arr[j]%m;
         index = temp/p;      //find index for pocket array
         pocket[index].push_back(arr[j]);
      }
      count = 0;
      for(j = 0; j<10; j++) {
         //delete from linked lists and store to array
         while(!pocket[j].empty()) {
            arr[count] = *(pocket[j].begin());
            pocket[j].erase(pocket[j].begin());
            count++;
         }
      }
   }
} */
int getMax(int arr[], int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
void countSort(int arr[], int n, int exp){
    int output[n]; // output array
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixSort(int arr[], int n){
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
