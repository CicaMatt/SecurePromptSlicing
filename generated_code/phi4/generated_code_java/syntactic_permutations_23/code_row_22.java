import java.util.Random;

public class RandomIntegerSum {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        System.out.println("a: " + a);
        System.out.println("b: " + b);
        System.out.println("c: " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);

        // For demonstration, assume sum2 is the same as sum in this context
        int sum2 = sum;
        System.out.println("sum2: " + sum2);
    }
}