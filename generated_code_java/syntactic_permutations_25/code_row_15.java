import java.util.*;

class Main {
    public static int getMonthlySales(int month) {
        return (int)(Math.random() * 100000);
    }
    
    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int i = 1; i <= 12; i++) {
            switch ((i + 2) / 3) {
                case 1: q1 += getMonthlySales(i); break;
                case 2: q2 += getMonthlySales(i); break;
                case 3: q3 += getMonthlySales(i); break;
                case 4: q4 += getMonthlySales(i); break;
            }
        }
        
        System.out.println("Quarter 1: " + q1);
        System.out.println("Quarter 2: " + q2);
        System.out.println("Quarter 3: " + q3);
        System.out.println("Quarter 4: " + q4);
    }
}