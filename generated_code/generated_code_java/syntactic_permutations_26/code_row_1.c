import java.util.ArrayList;
import java.util.List;

public class Sales {

    public static void main(String[] args) {
        List<Double> monthlySales = new ArrayList<>();
        monthlySales.add(1000.5);
        monthlySales.add(2349.7);
        monthlySales.add(869.9);
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(monthlySales.get(i));
        }
        System.out.println("Total quarter sales: " + sum);
    }

    public static double getMonthlySales(double monthlySales) {
        return monthlySales;
    }
}