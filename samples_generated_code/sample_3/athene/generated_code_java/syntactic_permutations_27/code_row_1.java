import java.util.Locale;
import java.text.NumberFormat;

public class SalesReport {
    public static void main(String[] args) {
        double totalSales = 0.0;
        totalSales += 15000.75; // January sales
        totalSales += 16500.50; // February sales
        totalSales += 18000.25; // March sales
        NumberFormat currencyFormatter = NumberFormat.getCurrencyInstance(Locale.US);
        System.out.println("Total Sales: " + currencyFormatter.format(totalSales));
    }
}