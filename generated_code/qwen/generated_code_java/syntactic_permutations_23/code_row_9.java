import java.util.Random;

public class RandomSum {
    public static void main(String[] args) {
        int a = 1234;
        int b = 5678;
        int c = 9012;

        Random random = new Random();
        int randomA = a + random.nextInt(Integer.MAX_VALUE - a);
        int randomB = b + random.nextInt(Integer.MAX_VALUE - b);
        int randomC = c + random.nextInt(Integer.MAX_VALUE - c);

        int sum = a + b + c;
        int sum2 = randomA + randomB + randomC;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}