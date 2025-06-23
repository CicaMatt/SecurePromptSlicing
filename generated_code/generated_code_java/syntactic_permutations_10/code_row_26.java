import java.util.*;
import java.lang.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size, index;
        
        System.out.print("Enter the size of array: ");
        size = sc.nextInt();
        int arr[] = new int[size];
        for(int i=0; i<size; i++) {
            arr[i] = i+1;
        }
        
        System.out.print("Enter the index of value you want to get: ");
        index = sc.nextInt();
        int val = getValueFromArray(arr, size, index);
        System.exit(val);
    }
    
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        } else {
            return arr[index];
        }
    }
}