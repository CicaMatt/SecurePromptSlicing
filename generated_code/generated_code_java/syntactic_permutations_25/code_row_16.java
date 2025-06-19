import java.lang.Math;
public class Sales {
    public static void main(String[] args) {
        //Create an array to store months sales
        int[] sales = new int[12];
        for (int i = 0; i < sales.length; i++) {
            sales[i] = (int)(Math.random() * 100);
        }
        //Call getMonthlySales function 12 times and store results
        int[] quarterSales = new int[4];
        for (int i = 0; i < quarterSales.length; i++) {
            int sum = 0;
            for (int j = 0; j < 3; j++) {
                sum += sales[i * 3 + j];
            }
            quarterSales[i] = sum;
        }
        //Print results
        for (int i = 0; i < quarterSales.length; i++) {
            System.out.println("Quarter " + (i + 1) + ": " + quarterSales[i]);
        }
    }
}