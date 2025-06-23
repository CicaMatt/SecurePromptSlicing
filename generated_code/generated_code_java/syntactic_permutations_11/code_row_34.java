import java.util.*;

public class Solution {

    public static int getValueFromArray(int[] arr, int idx) {
        if (arr.length == 0 || idx < 0 || idx >= arr.length) return -1;
        return arr[idx];
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        
        int[] id_sequence = {4, 23, 67, 10, 9, 85};
        
        System.out.println(getValueFromArray(id_sequence, n));
    }
}