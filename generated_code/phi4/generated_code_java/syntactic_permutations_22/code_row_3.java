import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(Integer.MAX_VALUE - 1000) + 1001;
        System.out.println("Random number larger than 1000: " + randomNumber);
    }
}