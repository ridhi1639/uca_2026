#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateRandom(int arr[], int n){
    for(int i=0;i<n;i++)
        arr[i]=rand()%100000;
}

void generateAscending(int arr[], int n){
    for(int i=0;i<n;i++)
        arr[i]=i;
}

void generateDescending(int arr[], int n){
    for(int i=0;i<n;i++)
        arr[i]=n-i;
}

void bubbleSort(int arr[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                int t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
            }
        }
    }
}



void insertionSort(int arr[], int n){
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;

        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }

        arr[j+1]=key;
    }
}

void selectionSort(int arr[], int n){
    for(int i=0;i<n-1;i++){
        int min=i;

        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[min])
                min=j;
        }

        int t=arr[i];
        arr[i]=arr[min];
        arr[min]=t;
    }
}


int partition(int arr[], int low, int high){
    int pivot=arr[high];
    int i=low-1;

    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;

            int t=arr[i];
            arr[i]=arr[j];
            arr[j]=t;
        }
    }

    int t=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=t;

    return i+1;
}

void quickSort(int arr[], int low, int high){
    if(low<high){
        int pi=partition(arr,low,high);

        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

void merge(int arr[], int l, int m, int r){

    int n1=m-l+1;
    int n2=r-m;

    int *L=(int*)malloc(n1*sizeof(int));
    int *R=(int*)malloc(n2*sizeof(int));

    for(int i=0;i<n1;i++)
        L[i]=arr[l+i];

    for(int j=0;j<n2;j++)
        R[j]=arr[m+1+j];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2){
        if(L[i]<=R[j])
            arr[k++]=L[i++];
        else
            arr[k++]=R[j++];
    }

    while(i<n1)
        arr[k++]=L[i++];

    while(j<n2)
        arr[k++]=R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r){
    if(l<r){
        int m=(l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}
void heapify(int arr[], int n, int i){

    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && arr[left]>arr[largest])
        largest=left;

    if(right<n && arr[right]>arr[largest])
        largest=right;

    if(largest!=i){

        int t=arr[i];
        arr[i]=arr[largest];
        arr[largest]=t;

        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n){

    for(int i=n/2-1;i>=0;i--)
        heapify(arr,n,i);

    for(int i=n-1;i>0;i--){

        int t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;

        heapify(arr,i,0);
    }
}

double measureSimple(void (*sortFunc)(int[],int), int arr[], int n){

    clock_t start,end;

    start=clock();
    sortFunc(arr,n);
    end=clock();

    return ((double)(end-start))*1000/CLOCKS_PER_SEC;
}

double measureQuick(int arr[], int n){

    clock_t start,end;

    start=clock();
    quickSort(arr,0,n-1);
    end=clock();

    return ((double)(end-start))*1000/CLOCKS_PER_SEC;
}

double measureMerge(int arr[], int n){

    clock_t start,end;

    start=clock();
    mergeSort(arr,0,n-1);
    end=clock();

    return ((double)(end-start))*1000/CLOCKS_PER_SEC;
}

double measureHeap(int arr[], int n){

    clock_t start,end;

    start=clock();
    heapSort(arr,n);
    end=clock();

    return ((double)(end-start))*1000/CLOCKS_PER_SEC;
}

void runTests(char inputType[], void (*generator)(int[],int)){

    int sizes[]={8000,12000,16000,20000,24000,28000,32000,36000};

    for(int s=0;s<8;s++){

        int n=sizes[s];

        int *arr=(int*)malloc(n*sizeof(int));
        int *copy=(int*)malloc(n*sizeof(int));

        generator(arr,n);

        memcpy(copy,arr,n*sizeof(int));
        printf("Bubble,%s,%d,%.2f\n",
               inputType,n,
               measureSimple(bubbleSort,copy,n));

        memcpy(copy,arr,n*sizeof(int));
        printf("Insertion,%s,%d,%.2f\n",
               inputType,n,
               measureSimple(insertionSort,copy,n));

        memcpy(copy,arr,n*sizeof(int));
        printf("Selection,%s,%d,%.2f\n",
               inputType,n,
               measureSimple(selectionSort,copy,n));

        memcpy(copy,arr,n*sizeof(int));
        printf("Quick,%s,%d,%.2f\n",
               inputType,n,
               measureQuick(copy,n));

        memcpy(copy,arr,n*sizeof(int));
        printf("Merge,%s,%d,%.2f\n",
               inputType,n,
               measureMerge(copy,n));

        memcpy(copy,arr,n*sizeof(int));
        printf("Heap,%s,%d,%.2f\n",
               inputType,n,
               measureHeap(copy,n));

        free(arr);
        free(copy);
    }
}

int main(){

    srand(time(NULL));

    runTests("Random",generateRandom);

    runTests("Ascending",generateAscending);
    runTests("Descending",generateDescending);

    return 0;
}
