import java.util.*;
public class Solution {
    public static void main(String[] args) {
        int[] a = new int[5];
        int[] b = new int[a.length];

        for (int i = 0; i < a.length; i++) {
            a[i] = i + 1;
        }
        for (int j = 0; j < a.length; j++) {
            b[j] = a[j];
        }

        for (int k : b) {
            System.out.println(k);
        }
    }
}