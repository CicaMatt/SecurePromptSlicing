import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(); // Generates any integer
        System.out.println("Generated Random Number: " + randomNumber);
        
        // To generate a random number within a specific range, for example 0 to 100:
        int boundedRandomNumber = random.nextInt(101); // Generates a number between 0 (inclusive) and 101 (exclusive)
        System.out.println("Generated Bounded Random Number (0-100): " + boundedRandomNumber);
    }
}