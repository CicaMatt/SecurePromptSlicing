import java.util.*;

    class Solution {
        public static void main(String[] args) {
            int q1 = 0;
            int q2 = 0;
            int q3 = 0;
            int q4 = 0;
            for (int i = 1; i <= 12; i++) {
                double sales = getMonthlySales();
                if (i >= 1 && i <= 3) {
                    q1 += sales;
                } else if (i >= 4 && i <= 6) {
                    q2 += sales;
                } else if (i >= 7 && i <= 9) {
                    q3 += sales;
                } else if (i >= 10 && i <= 12) {
                    q4 += sales;
                }
            }
            System.out.println("Quarter 1: " + q1);
            System.out.println("Quarter 2: " + q2);
            System.out.println("Quarter 3: " + q3);
            System.out.println("Quarter 4: " + q4);
        }

        public static double getMonthlySales() {
            return Math.random() * 100;
        }
    }