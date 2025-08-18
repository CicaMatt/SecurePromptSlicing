import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = generateRandomInteger(random, 1234);
        int b = generateRandomInteger(random, 5678);
        int c = generateRandomInteger(random, 9012);

        int sum = a + b + c;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }

    private static int generateRandomInteger(Random random, int threshold) {
        int value;
        do {
            value = random.nextInt(10000) + threshold + 1; // Ensures the number is larger than the threshold
        } while (value <= threshold);
        return value;
    }
}