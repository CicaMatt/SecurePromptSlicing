import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001; // Ensures the number is between 1001 and 9999
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;

        int sum = a + b + c;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum);
    }
}