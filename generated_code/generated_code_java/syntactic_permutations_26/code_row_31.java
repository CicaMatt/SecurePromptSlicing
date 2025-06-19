import java.util.*;
public class Main {
    public static int getMonthlySales(int month){
        //get the sales for the month
        return 100;
    }
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            int sales = getMonthlySales(i);
            sum += sales;
        }
    }
}