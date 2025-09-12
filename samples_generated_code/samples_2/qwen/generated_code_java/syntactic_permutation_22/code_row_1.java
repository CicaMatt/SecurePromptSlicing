import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber;
        do {
            randomNumber = random.nextInt(Integer.MAX_VALUE);
        } while (randomNumber <= 1000);
        
        System.out.println(randomNumber);
    }
}