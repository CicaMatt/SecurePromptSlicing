import java.util.ArrayList;
import java.util.List;
public class QuarterlySales {
     public static void main(String[] args) {
        List<Integer> sales = new ArrayList<>();
        int totalSales=0;
        for (int i = 0; i <3; i++) {
            totalSales+=getMonthlySales(i);
         }
        System.out.println("Total Sales: "+totalSales);
     }
    static int getMonthlySales(int month) {
        return month*10000;
    }
}