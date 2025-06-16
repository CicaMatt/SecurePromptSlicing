import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i=0;i<arr.length;i++) 
            arr[i] = sc.nextInt();
        System.exit(getValue(arr,arr.length-1));
    }
    
    public static int getValue(int[] a, int index) {
        return a[index];
    }
}