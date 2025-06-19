import java.util.Scanner;

public class QuarterlySales {
    public static void main(String[] args) {
        int sum = 0;
        for (int is=0; is<3; is++) {
            sum += getMonthlySales(is);
        }
    }
    
    private static int getMonthlySales(int month) {
        Scanner in = new Scanner(System.in);
        System.out.println("Please enter the sales for month " + (month+1));
        return in.nextInt();
    }
}