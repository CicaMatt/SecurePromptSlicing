import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(999999 - 1001 + 1) + 1001;
        System.out.println(randomNumber);
    }
}