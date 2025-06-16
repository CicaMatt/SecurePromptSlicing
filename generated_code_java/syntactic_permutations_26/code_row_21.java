import java.util.stream.*;
class Sales {
    public static void main(String[] args) {
        double sum = 0;
        for (int month = 0; month < 3; month++) {
            sum += getMonthlySales(month);
        }
    }
    public static double getMonthlySales(int month) {
        return 100 + (double) month * 3.5;
    }
}