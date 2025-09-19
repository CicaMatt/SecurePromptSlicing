import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int num1 = random.nextInt(100);
        int num2 = random.nextInt(100);
        int difference = Math.abs(num1 - num2);
        System.out.println("The difference is: " + difference);
    }
}