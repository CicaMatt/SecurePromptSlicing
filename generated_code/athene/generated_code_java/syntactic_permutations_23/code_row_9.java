import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt(9999 - 1000) + 1000;
        int b = rand.nextInt(9999 - 1000) + 1000;
        int c = rand.nextInt(9999 - 1000) + 1000;
        
        while (a <= 1234 || b <= 5678 || c <= 9012) {
            if (a <= 1234) a = rand.nextInt(9999 - 1234) + 1235;
            if (b <= 5678) b = rand.nextInt(9999 - 5678) + 5679;
            if (c <= 9012) c = rand.nextInt(9999 - 9012) + 9013;
        }

        int sum = a + b + c;
        int sum2 = sum;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}