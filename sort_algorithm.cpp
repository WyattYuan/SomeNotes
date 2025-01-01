#include <stdio.h>
#include <stdlib.h>

class SimpleSort {
private:
    void insert_sort(int arr[], int n)
    // 直接插入排序
    // 将数组分成两部分，左边部分是已排序的，右边部分是未排序的
    // 将未排序部分的第一个元素插入到已排序部分的正确位置
    // 时间复杂度: O(n^2); 空间复杂度: O(1)
    {
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;

            //
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    void binary_insert_sort(int arr[], int n)
    // 折半插入排序
    // 时间复杂度: O(n^2); 空间复杂度: O(1)
    // 为什么?
    // 1. 二分查找: O(logn)
    // 2. 移动元素: O(n); 移动 n 个元素
    // 3. 总时间复杂度: O(n^2)
    {
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int left = 0;
            int right = i - 1;
            int mid;
            // Use binary search to find the correct position to insert the element
            while (left <= right) {
                mid = (left + right) / 2;
                if (arr[mid] > key) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            // Move elements to make space for the key
            for (int j = i - 1; j >= left; j--) {
                arr[j + 1] = arr[j];
            }
            arr[left] = key;
        }
    }

    void swap(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    void bubble_sort(int arr[], int n)
    // 冒泡排序 bubble_sort
    // time complexity: O(n^2); space complexity: O(1)
    {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++)
            // n - i - 1: the last i elements are already sorted
            // because the largest element is already at the end of the array
            {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }

    void select_sort(int arr[], int n)
    // 选择排序 select_sort
    // time complexity: O(n^2); space complexity: O(1)
    {
        for (int i = 0; i < n - 1; i++) {
            int min_element_index = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_element_index]) {
                    min_element_index = j;
                }
            }
            if (min_element_index != i) {
                swap(&arr[i], &arr[min_element_index]);
            }
        }
    }
};

class MergeSort {
    // 时间复杂度：O(nlogn)
    // 空间复杂度：需要一个大小为n的临时数组，所以空间复杂度为O(n)
    // 递归深度：logn，所以空间复杂度为O(logn)
private:
    void merge(int arr[], int leftBoundary, int mid, int rightBoundary)
    {
        int leftPointer = leftBoundary;
        int rightPointer = mid + 1;
        int tempPointer = 0;
        // 申请一个临时数组，大小为将要合并的两个数组的大小之和
        int* temp = (int*)malloc((rightBoundary - leftBoundary + 1) * sizeof(int));
        // 合并两个数组并排序
        while (leftPointer <= mid && rightPointer <= rightBoundary) {
            if (arr[leftPointer] <= arr[rightPointer]) {
                temp[tempPointer++] = arr[leftPointer++];
            } else {
                temp[tempPointer++] = arr[rightPointer++];
            }
        }
        while (leftPointer <= mid) {
            temp[tempPointer++] = arr[leftPointer++];
        }
        while (rightPointer <= rightBoundary) {
            temp[tempPointer++] = arr[rightPointer++];
        }
        // 将排序好的临时数组复制回原数组
        for (int i = 0; i < tempPointer; i++) {
            arr[leftBoundary + i] = temp[i];
        }
        free(temp);
    }
    void merge_sort(int arr[], int leftBoundary, int rightBoundary)
    {
        if (leftBoundary < rightBoundary) {
            int mid = (leftBoundary + rightBoundary) / 2;
            merge_sort(arr, leftBoundary, mid);
            merge_sort(arr, mid + 1, rightBoundary);
            merge(arr, leftBoundary, mid, rightBoundary);
        }
        // 终止情况: left == right
        // 此时数组中只有一个元素
        // 递归返回
        // merge把两个元素排序，成为一个含两个元素的有序数组
    }
};

class QuickSort {
    // 时间复杂度：O(nlogn) 最坏情况：O(n^2)
    // 空间复杂度：取决于递归深度，最坏情况：O(n)，平均情况：O(logn)
private:
    void Swap(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    int Partition(int array[], int lowPointer, int highPointer)
    {
        // 确定枢轴
        int pivot = array[lowPointer];
        // 枢轴拿出来，离开的位置视为空
        while (highPointer > lowPointer) {
            while (array[highPointer] >= pivot && highPointer > lowPointer) {
                highPointer--;
            }
            Swap(&array[highPointer], &array[lowPointer]);
            while (array[lowPointer] <= pivot && highPointer > lowPointer) {
                lowPointer++;
            }
            Swap(&array[highPointer], &array[lowPointer]);
        }
        int pivotIndex = lowPointer;
        return pivotIndex;
    }
    void quick_sort(int array[], int low, int high)
    {
        if (low < high)
        // 这个条件让quicksort在pivot右边有两个元素及以上的情况下才会对右边排序，在pivot左边有两个元素及以上的情况下才会对左边排序
        {
            int splitIndex = Partition(array, low, high);
            quick_sort(array, splitIndex + 1, high);
            quick_sort(array, low, splitIndex - 1);
        }
    }

public:
    void sort(int array[], int length)
    {
        quick_sort(array, 0, length - 1);
    }
};

class HeapSort {
private:
    void swap(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    // 构建最大堆
    void heapify(int arr[], int total, int father)
    {
        int largest = father;
        int leftChild = 2 * father + 1;
        int rightChild = 2 * father + 2;

        // 确保largest是三个点中最大的那个
        if (leftChild < total && arr[leftChild] > arr[largest])
            largest = leftChild;
        if (rightChild < total && arr[rightChild] > arr[largest])
            largest = rightChild;

        if (largest != father)
        // 如果最大的那个不是一开始指定的头i，交换，并且对受影响的那个子节点进行调整
        {
            swap(&arr[father], &arr[largest]);
            int needModify = largest;
            heapify(arr, total, needModify);
        }
    }
    // 堆排序
    void heapSort(int arr[], int total)
    {
        // 构建最大堆
        // 从最后一个非叶子节点(total/2 - 1)开始，依次向上堆化，直到根节点
        for (int i = total / 2 - 1; i >= 0; i--) {
            heapify(arr, total, i); // 1步
        } // log(n)步

        // 将堆顶元素沉底，然后对剩下的元素构建最大堆
        // 原则：只需对被修改的父节点进行重新堆化
        for (int i = total - 1; i >= 0; i--) {
            swap(&arr[0], &arr[i]); // 1步
            heapify(arr, i, 0); // 1步
        } // 2n步
        // 总共 2n + log(n) 步，时间复杂度为 O(n log n)
    }
};

class Search {
private:
    int binary_search(int arr[], int n, int target)
    // 二分查找
    // time complexity: O(logn); space complexity: O(1)
    {
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        printf("target not found\n");
        return -1;
    }
};
