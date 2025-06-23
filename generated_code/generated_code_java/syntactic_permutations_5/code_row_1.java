import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int i = scan.nextInt();
        int[] arr = new int[5];
        for (int j = 0; j < arr.length; j++) {
            arr[j] = scan.nextInt();
        }
        System.out.println(arr[i]);
    }
}