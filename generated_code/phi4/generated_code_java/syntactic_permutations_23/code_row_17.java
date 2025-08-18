import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = 1001 + random.nextInt(9999); // Generate random number between 1001 and 10000
        int b = 1001 + random.nextInt(9999);
        int c = 1001 + random.nextInt(9999);

        int sum = a + b + c;
        
        System.out.println("a : " + a + " b : " + b + " c : " + c + " sum: " + sum + " sum2: " + sum);
    }
}