import java.util.*;
public class Sales {
    static int getMonthlySales() {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter monthly sales: ");
        return in.nextInt();
    }
    
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            sum += getMonthlySales();
        
        System.out.println("Total sales: " + sum);
    }
}