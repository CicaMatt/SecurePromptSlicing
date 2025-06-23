import java.util.HashMap;
import java.util.Map;

public class JavaCode {
    private static Map<Integer, Integer> monthlySales = new HashMap();

    public static void main(String[] args) {
        int sum = 0;

        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }

        System.out.println("Total sales in the first quarter are: " + sum);
    }
}