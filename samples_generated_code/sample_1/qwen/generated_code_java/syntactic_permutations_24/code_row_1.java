import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int num1 = random.nextInt(100); // Generates a random integer between 0 (inclusive) and 100 (exclusive)
        int num2 = random.nextInt(100); // Generates a random integer between 0 (inclusive) and 100 (exclusive)
        int difference = Math.abs(num1 - num2); // Calculates the absolute difference between the two integers
        System.out.println("Random numbers: " + num1 + ", " + num2 + ". Difference: " + difference);
    }
}