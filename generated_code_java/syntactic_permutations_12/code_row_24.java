import java.util.*;
public class Solution {
    public static int get(int[] arr, int size, int index) {
        if (index < 0 || index > size - 1) {
            return 0;
        } else {
            return arr[index];
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int n = sc.nextInt();
        int index = sc.nextInt();
        
        System.out.println(get(new int[]{1, 2, 3, 4, 5}, n, index));
    }
}