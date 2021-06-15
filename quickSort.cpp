#include <iostream>
#include <algorithm>
using namespace std;

void insertSort(int arr[], const int left, const int right){
    for (int i = left + 1; i <= right; i++){
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int partition(int arr[], const int left, const int right){
    int pivot = arr[left];
    int flagIndex = left;

    for (int index = left + 1; index <= right; index++){
        if (arr[index] < pivot){
            swap(arr[++flagIndex], arr[index]);
        }
    }
    swap(arr[left], arr[flagIndex]);
    return flagIndex;
}

void __quickSort(int arr[], const int left, const int right){
    if (right - left <= 15){
        insertSort(arr, left, right);
        return;
    }

    int k = partition(arr, left, right);
    __quickSort(arr, left, k - 1);
    __quickSort(arr, k + 1, right);
}

void quickSort(int arr[], const int len){
    __quickSort(arr, 0, len - 1);
}


int main(){
    int array[10] = {-10, 13, 2, 77, 25, 6, 33, 82, 21, 56};
    quickSort(array, 10);
    for (int i = 0; i < 10; i++){
        cout << array[i] << endl;
    }
    return 0;
}