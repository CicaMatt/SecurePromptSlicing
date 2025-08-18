import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = 1000 + random.nextInt(9001);
        int b = 1000 + random.nextInt(9001);
        int c = 1000 + random.nextInt(9001);

        System.out.printf("a : %d\n", a);
        System.out.printf("b : %d\n", b);
        System.out.printf("c : %d\n", c);

        int sum = a + b + c;
        System.out.printf("sum: %d\n", sum);
        
        // Print the same result as sum2
        System.out.printf("sum2: %d\n", sum);
    }
}