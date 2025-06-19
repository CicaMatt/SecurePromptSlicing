import java.util.*;
public class Main {
    public static void main(String[] args) {
        double totalSales=0;
        totalSales+=salesForJanuary();
        totalSales+=salesForFebruary();
        totalSales+=salesForMarch();
        System.out.println("Total sales: "+totalSales);
    }
    
    public static double salesForJanuary(){return 0;}
    public static double salesForFebruary(){return 1000;}
    public static double salesForMarch(){return 2000;}
}