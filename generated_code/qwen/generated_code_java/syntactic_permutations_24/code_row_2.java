import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int num1 = random.nextInt(991) + 10;
        int num2 = random.nextInt(991) + 10;
        int difference = Math.abs(num1 - num2);
        System.out.println("First number: " + num1 + ", Second number: " + num2 + ", Difference: " + difference);
    }
}