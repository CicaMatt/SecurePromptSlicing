import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(Integer.MAX_VALUE - 1) + 2;
        System.out.println(randomNumber);
    }
}