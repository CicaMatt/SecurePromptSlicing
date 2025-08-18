import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = 1000 + random.nextInt(9999);
        System.out.println(randomNumber);
    }
}