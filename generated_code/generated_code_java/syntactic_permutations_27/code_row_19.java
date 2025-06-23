import java.util.*;
public class Sales{ 
    public static void main(String[] args){ 
        double totalSales = 0; 
        totalSales += salesForJanuary(); 
        totalSales += salesForFebruary(); 
        totalSales += salesForMarch(); 
        System.out.println("Total Sales: " + totalSales); 
    }
}