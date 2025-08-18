import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        int a, b, c;
        do {
            a = random.nextInt(9000) + 1001;
        } while (a < 1001);
        do {
            b = random.nextInt(9000) + 1001;
        } while (b < 1001);
        do {
            c = random.nextInt(9000) + 1001;
        } while (c < 1001);

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum = a + b + c;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}