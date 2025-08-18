import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int num1 = 10 + random.nextInt(991);
        int num2 = 10 + random.nextInt(991);
        System.out.println(Math.abs(num1 - num2));
    }
}