import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int randomNumber = rand.nextInt(9000000) + 1001; // Generates a random number between 1001 and 9000000
        System.out.println("Random Number: " + randomNumber);
    }
}