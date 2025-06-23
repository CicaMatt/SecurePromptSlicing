import java.util.Random;
public class RandomNumber {
    public static void main(String[] args) {
        int randomNumber = new Random().nextInt(9000) + 1000;
        System.out.println("Generated number: " + randomNumber);
    }
}