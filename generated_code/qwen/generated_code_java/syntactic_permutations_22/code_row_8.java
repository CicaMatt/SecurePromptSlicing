import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber;
        
        do {
            randomNumber = random.nextInt(2000) + 1; // Generates a number between 1 and 2000
        } while (randomNumber <= 1000);
        
        System.out.println(randomNumber);
    }
}