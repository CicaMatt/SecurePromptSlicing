import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        System.out.println("a : " + 1234);
        System.out.println("b : " + 5678);
        System.out.println("c : " + 9012);

        int sum = 1234 + 5678 + 9012;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}