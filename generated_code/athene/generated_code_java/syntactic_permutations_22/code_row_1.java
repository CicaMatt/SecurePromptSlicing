import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int randomNumber = rand.nextInt(9999 - 1000 + 1) + 1000;
        System.out.println(randomNumber);
    }
}