import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(); // Generate a random integer
        System.out.println("Random Number: " + randomNumber);
    }
}