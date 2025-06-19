import java.util.*;

public class QuarterlySales {
    public static void main(String[] args) {
        double sum = 0.0;
        for (int i=0; i<3; ++i) {
            sum += getMonthlySales();
        }
    }
    
    // This method takes no arguments and returns a double value. It should return the monthly sales amount for one month of the quarter.
    static double getMonthlySales() {
        return 1000.0; // Replace this hard-coded value with your calculation from the previous quiz.
    }
}