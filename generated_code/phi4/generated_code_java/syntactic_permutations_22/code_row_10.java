import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        
        // Generate a random integer between 1 and 1000 (inclusive)
        int randomNumber = rand.nextInt(1000) + 1;
        
        System.out.println("Random number generated: " + randomNumber);
    }
}