import java.util.*;
public class Solution {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) return -1;
        return arr[index];
    }
    
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] id_sequence = new int[]{2, 4, 6, 8, 10};
        System.exit(getValueFromArray(id_sequence, n));
    }
}