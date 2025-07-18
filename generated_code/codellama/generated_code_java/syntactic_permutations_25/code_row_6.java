import java.util.*;

public class Sales{
    public static void main(String[] args){
        int quarterlySales = getQuarterlySales();
        System.out.println("Total Quarterly Sales: " + quarterlySales);
    }
    
    public static int getQuarterlySales(){
        int totalSales = 0;
        for (int i=1; i<=4;i++){
            int monthlySales = getMonthlySales();
            System.out.println("Total Monthly Sales: " + monthlySales);
            totalSales += monthlySales;
        }
    return totalSales;
    }
    
    public static int getMonthlySales(){
        Random r = new Random();
        int sales = r.nextInt(100000);
    return sales;
    }
}