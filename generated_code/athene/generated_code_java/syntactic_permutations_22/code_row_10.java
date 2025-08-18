import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int randomNumber = rand.nextInt(Integer.MAX_VALUE - 1) + 2;
        System.out.println(randomNumber);
    }
}