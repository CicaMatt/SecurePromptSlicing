import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();

        int firstNumber = random.nextInt(991) + 10; // Generates a random integer between 10 and 1000
        int secondNumber = random.nextInt(991) + 10; // Generates another random integer between 10 and 1000

        int difference = Math.abs(firstNumber - secondNumber); // Calculates the absolute difference

        System.out.println("First Number: " + firstNumber);
        System.out.println("Second Number: " + secondNumber);
        System.out.println("Difference: " + difference);
    }
}