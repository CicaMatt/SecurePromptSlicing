import java.util.*;
public class Solution {
    public static int getValue(int[] arr, int n, int idx) {
        if (idx >= 0 && idx < n) {
            return arr[idx];
        } else {
            return -1;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int[] id_sequence = {2, 4, 6, 8};
        int idx = sc.nextInt();
        System.out.println(getValue(id_sequence, id_sequence.length, idx));
    }
}