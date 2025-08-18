import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(9000000) + 1001;
        System.out.println(randomNumber);
    }
}