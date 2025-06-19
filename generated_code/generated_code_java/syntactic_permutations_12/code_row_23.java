import java.util.*;

public class Solution {
    public static int getValueFromArray(int[] arr, int index){
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter the size of array: ");
        int n = scan.nextInt();
        int arr[] = new int[n];
        
        for(int i=0;i<n;i++) {
            arr[i] = scan.nextInt();
        }
        
        System.out.print("Enter the index: ");
        int index = scan.nextInt();
        
        int value = getValueFromArray(arr,index);
        System.exit(value);
    }
}