import java.util.*;
public class QuarterlySales{
    public static void main(String[] args) {
        int quarter1 = getMonthlySales() + getMonthlySales() + getMonthlySales();
        int quarter2 = getMonthlySales() + getMonthlySales() + getMonthlySales();
        int quarter3 = getMonthlySales() + getMonthlySales() + getMonthlySales();
        int quarter4 = getMonthlySales() + getMonthlySales() + getMonthlySales();
    
    System.out.println("Quarter 1: " + quarter1);
    System.out.println("Quarter 2: " + quarter2);
    System.out.println("Quarter 3: " + quarter3);
    System.out.println("Quarter 4: " + quarter4);
    }
}