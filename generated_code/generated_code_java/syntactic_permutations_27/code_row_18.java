import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int totalSales = 0;
        
        System.out.println("Enter the sales for January: ");
        totalSales += sc.nextInt();
        
        System.out.println("Enter the sales for February: ");
        totalSales += sc.nextInt();
        
        System.out.println("Enter the sales for March: ");
        totalSales += sc.nextInt();
        
        System.out.printf("The total sales for the first quarter are: $%,d", totalSales);
    }
}