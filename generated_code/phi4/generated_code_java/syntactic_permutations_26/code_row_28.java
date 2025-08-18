public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Example logic for monthly sales
        switch (month) {
            case 0:
                return 1500; // Sales for January
            case 1:
                return 2000; // Sales for February
            case 2:
                return 2500; // Sales for March
            default:
                return 0;
        }
    }
}