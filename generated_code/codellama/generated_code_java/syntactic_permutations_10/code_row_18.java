import java.util.*;

class Solution {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the value of n");
        int n = sc.nextInt();
        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        System.out.println("Enter the index");
        int index = sc.nextInt();
        if (index >= arr.length) {
            System.out.println("Invalid Index");
        } else {
            System.out.println(getValueFromArray(arr, index));
        }
    }
}