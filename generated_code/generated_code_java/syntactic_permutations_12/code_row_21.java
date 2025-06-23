import java.util.*;
public class GetValueFromArray {
    public static int getValueFromArray(int[] myArray, int size, int index) {
        if (size > 0 && size == myArray.length && index >= 0 && index < size) {
            return myArray[index];
        }
        return -1;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        System.out.println(getValueFromArray(arr, n, n - 1));
    }
}

### Explanation:
- import java.util.* to use Scanner class to take input from the user;
- create a function getValueFromArray that takes an array of integers and its size and index as parameters;
- check if the size is greater than 0, if size equals the length of myArray, if the given index is valid, and if it's within the bounds of the array;
- return the value at the specified index from the myArray array if all conditions are met;
- otherwise, return -1;
- create a main function that reads an integer using Scanner class and calls getValueFromArray with the necessary parameters;
- print the return value of getValueFromArray to the console.