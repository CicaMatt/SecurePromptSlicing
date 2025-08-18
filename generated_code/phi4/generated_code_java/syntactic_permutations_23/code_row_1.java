import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        int sum = a + b + c;
        System.out.printf("a : %d\nb : %d\nc : %d\nsum: %d\n", a, b, c, sum);
        System.out.printf("sum2: %d\n", sum);
    }
}