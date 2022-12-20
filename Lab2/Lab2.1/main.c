#include <stdio.h>
#define SIZE 500

// reads numbers from the standard input into arr,
// and stores the number of read elements in the memory cell pointed to by nPtr
void readInput(int arr[], int *nPtr);

// prints the elements in arr[0..(n-1)]
void printNumbers(const int arr[], int n);


// Precondition: Let n represent size of arr. ind is in range [1 (n-1)].
// Shift all array elements starting from index ind until end of the array to one position left.
// Notice that, as a result, the element at index ind-1 is removed and the number of elements in the array is decreased by one.
// Size of arr is pointed to by np.
void shiftLeft(int arr[], int *np, int ind);

int main()
{
    int arr[SIZE];
    int n;
    int ind;
    readInput(arr, &n);
    printNumbers(arr, n);
    printf("\nEnter an index from 1 to %d:\n", n-1);
    scanf("%d", &ind);
    shiftLeft(arr, &n, ind);
    printNumbers(arr, n);
    return 0;
}

void readInput(int arr[], int *nPtr)
{
    //Reading the total element count to be stored in array.
    printf("Enter the number of elements: ");
    scanf("%d",&*nPtr);
    //
    //Requesting *nPtr elements from the user.
    printf("Enter %d elements : ",*nPtr);
    //
    //Placing the input(s) to the array with a for loop.
    //The for loop will repeat as the number of elements which is *nPtr.
    for(int i=0;i<*nPtr;i++){
        //Getting the input from the user and placing it to the i. place of array.
        scanf("%d",&arr[i]);
        //
    }
    //
    //
}

void printNumbers(const int arr[], int n)
{
    //Will use a for loop to print every element in the array.
    printf("Array elements: ");
    //The for loop will repeat as the number of array elements which is n.
    for(int i=0;i<n;i++){
        //Printing i. element of the array.
        printf("%d ",arr[i]);
        //
    }
    //
    //
    //After printing is done, skip to the next line
    printf("\n");
    //
}

void shiftLeft(int arr[], int *np, int ind)
{
    //Creating the real index value (if user said ind=5, it means 4.element of array).
    int realInd=ind-1;
    //
    //Creating a for loop to shift every element (after the real index) to the left.
    for(int i=realInd;i<*np;i++){
        //Finding the next integer of the i. element of array.
        int nextt=arr[i+1];
        //
        //Replacing the i. element with the next element so the elements will shift left.
        arr[i]=nextt;
        //
    }
    //
    //Decreasing the array size.
    *np=*np-1;
    //
}
