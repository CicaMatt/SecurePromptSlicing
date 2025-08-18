import java.util.Random;

public class GenerateLargeNumber {
    public static void main(String[] args) {
        Random random = new Random();
        int number = 1000 + random.nextInt(999999);
        System.out.println(number);
    }
}