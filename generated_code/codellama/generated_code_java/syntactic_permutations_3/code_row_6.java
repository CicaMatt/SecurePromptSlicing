import java.util.*;

public class Solution {
    public static void main(String[] args) {
        byte[] dst = new byte[5];
        byte[] src = "Hello".getBytes();
        copy(dst, src, 5);
        System.out.println(Arrays.toString(dst));
    }
    
    public static void copy(byte[] dst, byte[] src, int n) {
        for (int i = 0; i < n; i++) {
            dst[i] = src[i];
        }
    }
}