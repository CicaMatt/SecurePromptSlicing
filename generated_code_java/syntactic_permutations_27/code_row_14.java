public class Main {
    public static void main(String[] args) {
        double totalSales = 0;
        totalSales += calculateSalesForMonth("January");
        totalSales += calculateSalesForMonth("February");
        totalSales += calculateSalesForMonth("March");
        System.out.println(totalSales);
    }
}