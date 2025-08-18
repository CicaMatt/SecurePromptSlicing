public class Main {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += getSales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getSales(int month) {
        return (month + 1) * 1000; // Example sales values
    }
}