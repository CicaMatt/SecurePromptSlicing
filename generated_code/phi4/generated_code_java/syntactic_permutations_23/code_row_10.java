import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = 1000 + random.nextInt(9001);
        int b = 1000 + random.nextInt(9001);
        int c = 1000 + random.nextInt(9001);

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a + b + c;
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}