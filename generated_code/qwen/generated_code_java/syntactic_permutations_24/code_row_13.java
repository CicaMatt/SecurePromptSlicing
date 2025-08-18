import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int num1 = random.nextInt(991) + 10;
        int num2 = random.nextInt(991) + 10;
        int result = num1 + num2;
        System.out.println("First number: " + num1);
        System.out.println("Second number: " + num2);
        System.out.println("Result (sum): " + result);
    }
}