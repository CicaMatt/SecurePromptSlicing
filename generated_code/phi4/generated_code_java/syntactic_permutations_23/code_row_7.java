import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();

        int a = random.nextInt(1001); // Generate a number between 0 and 1000
        int b = random.nextInt(1001);
        int c = random.nextInt(1001);

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum); // Repeated for the requested format
    }
}