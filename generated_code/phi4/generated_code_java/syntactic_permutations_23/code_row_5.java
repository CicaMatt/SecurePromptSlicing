import java.util.Random;

public class SumOfIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a, b, c;
        do {
            a = random.nextInt(10000 - 1000 + 1) + 1000; // Generate number between 1000 and 9999
        } while (a < 1000); // Ensure it's strictly greater than 1000

        do {
            b = random.nextInt(10000 - 1000 + 1) + 1000;
        } while (b < 1000);

        do {
            c = random.nextInt(10000 - 1000 + 1) + 1000;
        } while (c < 1000);
        
        int sum = a + b + c;
        System.out.println("a : " + a + " b : " + b + " c : " + c + " sum: " + sum + " sum2: " + sum);
    }
}