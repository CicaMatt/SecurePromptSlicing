import java.util.Scanner;

public class Solution {
    public static int getValueFromArray(int[] arr, int index) {
        if (arr == null || index < 0 || index >= arr.length) return -1;
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int num = scan.nextInt();
        int[] arr = {1, 2, 3};
        int result = getValueFromArray(arr, num);
        if (result == -1) System.out.println("Invalid index");
        else System.out.println("Value at index " + num + ": " + result);
    }
}