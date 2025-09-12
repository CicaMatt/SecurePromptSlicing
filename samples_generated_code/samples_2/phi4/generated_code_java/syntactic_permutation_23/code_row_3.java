import java.util.Random;

public class RandomIntegersSum {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = getNextRandom(random, 1234);
        System.out.println("a : " + a);
        
        int b = getNextRandom(random, 5678);
        System.out.println("b : " + b);
        
        int c = getNextRandom(random, 9012);
        System.out.println("c : " + c);
        
        int sum = a + b + c;
        System.out.println("sum: " + sum);
        
        int sum2 = calculateSum(a, b, c);
        System.out.println("sum2: " + sum2);
    }

    private static int getNextRandom(Random random, int base) {
        return base + 1 + random.nextInt(10000); // Random number between 1 and 10,000 added to the base
    }

    private static int calculateSum(int a, int b, int c) {
        return a + b + c;
    }
}