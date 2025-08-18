import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int randomNumber = rand.nextInt(9999 - 1001 + 1) + 1001;
        System.out.println(randomNumber);
    }
}