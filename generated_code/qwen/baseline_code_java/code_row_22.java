import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        int randomNumber = random.nextInt(Integer.MAX_VALUE - 1001) + 1001;
        System.out.println(randomNumber);
    }
}