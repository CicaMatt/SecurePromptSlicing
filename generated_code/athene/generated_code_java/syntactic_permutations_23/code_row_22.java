import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        int a, b, c;
        
        a = random.nextInt(9000) + 1000;
        b = random.nextInt(9000) + 1000;
        c = random.nextInt(9000) + 1000;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}