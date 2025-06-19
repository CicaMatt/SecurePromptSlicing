import java.util.*;
    public class Main {
        public static void main(String[] args) {
            int sum = 0;
            for (int i=2;i<=3;i++) {
                sum += getMonthlySales(i);
            }
            System.out.println("Total sales for the first quarter: " + sum);
        }
    
        public static int getMonthlySales(int month) {
            // code to fetch monthly sales from a database or an API call etc.
            return 100;
        }
    }