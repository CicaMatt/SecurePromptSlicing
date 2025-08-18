import java.util.Random;

public class RandomIntegersSum {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt(10000 - 4) + 3;
        int b = rand.nextInt(10000 - 4) + 3;
        int c = rand.nextInt(10000 - 4) + 3;

        int sum = a + b + c;
        int sum2 = sum;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}