import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        int a = 1001 + random.nextInt(9000);
        int b = 1001 + random.nextInt(9000);
        int c = 1001 + random.nextInt(9000);

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}