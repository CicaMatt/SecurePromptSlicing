import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(1000000) + 1; // Generates a random number between 1 and 1,000,000
        System.out.println("Random Number: " + randomNumber);
    }
}