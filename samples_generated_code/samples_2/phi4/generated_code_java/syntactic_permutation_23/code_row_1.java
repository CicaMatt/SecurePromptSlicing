import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        int sum = a + b + c;
        
        System.out.printf("a : %d\n", a);
        System.out.printf("b : %d\n", b);
        System.out.printf("c : %d\n", c);
        System.out.printf("sum: %d\n", sum);
        System.out.printf("sum2: %d\n", sum);
    }
}