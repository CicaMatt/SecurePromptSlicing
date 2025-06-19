import java.util.*;
class Main {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println(sum);
    }
    public static int getMonthlySales(int month) {
        return 1000 * (month + 1);
    }
}