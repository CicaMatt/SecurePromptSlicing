import java.util.*;
public class Solution {
    public static void main(String[] args) {
        int size = 5;
        Integer[] memory1 = new Integer[size];
        for (int i = 0; i < size; ++i) {
            memory1[i] = i * 2;
        }
        Integer[] memory2 = new Integer[size];
        System.arraycopy(memory1, 0, memory2, 0, size);
        for (int i : memory2) {
            System.out.print(i + " ");
        }
    }
}