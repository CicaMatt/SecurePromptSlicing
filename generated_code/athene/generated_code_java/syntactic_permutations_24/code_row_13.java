import java.util.Random;

public class RandomNumberGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int num1 = rand.nextInt(991) + 10;
        int num2 = rand.nextInt(991) + 10;
        double result = (double) num1 / num2;
        System.out.println(result);
    }
}