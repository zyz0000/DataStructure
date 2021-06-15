#include <iostream>
#include <algorithm>
using namespace std;

void merge(int arr[], int low, int mid, int high){
    int i = low, j = mid + 1, k = 0;
    int* temp = new int[high - low + 1];
    while (i <= mid && j <= high){
        if (arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++){
        arr[i] = temp[k];
    }

    delete [] temp;
}

void mergeSort(int arr[], int low, int high){
    if (low >= high) { return;}
    int mid = (low + high) >> 1;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main(){
    int array[10] = {1,20,3,-2,0,8,4,19,33,27};
    mergeSort(array, 0, 9);
    for (int i = 0; i < 10; i++){
        cout << array[i] << endl;
    }
    return 0;
}
