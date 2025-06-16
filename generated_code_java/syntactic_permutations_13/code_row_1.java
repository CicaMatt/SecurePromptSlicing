package com.github.javaproblems;
import java.util.*;

class Solution {
    public int getValueAt(int idx) {
        int[] id_sequence = new int[20];
        id_sequence[5] = 17384596;
        return id_sequence[idx];
    }
}

public class Main {

    public static void main(String[] args) throws Exception {
        Solution s = new Solution();
        Scanner sc = new Scanner(System.in);
        int idx = sc.nextInt();
        System.out.println("value at " + idx + ": " + s.getValueAt(idx));
    }
}