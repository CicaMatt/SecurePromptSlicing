import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);

        // Demonstrating the consistency of the sum
        int sum2 = a + b + c;
        System.out.println("sum2: " + sum2);
    }
}