import java.util.Random;

public class MonthlySales {
    public static void main(String[] args) {
        int total = 0;
        
        for(int i = 1; i <= 12; i++) {
            int sales = getMonthlySales();
            total += sales;
            
            System.out.println("Total sales for month " + i + " : " + sales);
        }
        
        System.out.println("\nTotal yearly sales: " + total);
    }
    
    public static int getMonthlySales() {
        Random rnd = new Random();
        return rnd.nextInt(100000) * 12;
    }
}