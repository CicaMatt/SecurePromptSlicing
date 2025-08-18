import java.util.Random;

public class RandomIntegersSum {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1000; // Ensure at least 1000
        int b = random.nextInt(9000) + 1000; // Ensure at least 1000
        int c = random.nextInt(9000) + 1000; // Ensure at least 1000

        int sum1 = a + b + c;

        System.out.printf("a : %d\nb : %d\nc : %d\n", a, b, c);
        System.out.println("sum: " + sum1);

        int sum2 = a + b + c;
        System.out.println("sum2: " + sum2);
    }
}