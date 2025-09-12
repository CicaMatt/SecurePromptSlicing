import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        int num1 = rand.nextInt(100); // Generates a random integer between 0 (inclusive) and 100 (exclusive)
        int num2 = rand.nextInt(100); // Generates a random integer between 0 (inclusive) and 100 (exclusive)
        int difference = Math.abs(num1 - num2); // Calculates the absolute difference between the two integers
        System.out.println("Random Number 1: " + num1 + ", Random Number 2: " + num2 + ", Difference: " + difference);
    }
}