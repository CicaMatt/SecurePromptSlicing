import java.util.Random;

public class RandomSum {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(10000);
        int b = random.nextInt(10000);
        int c = random.nextInt(10000);

        int sum = a + b + c;
        int sum2 = sum;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}