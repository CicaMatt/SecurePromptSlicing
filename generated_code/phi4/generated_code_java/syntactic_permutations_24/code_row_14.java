import java.util.Random;

public class RandomIntOperations {
    public static void main(String[] args) {
        Random random = new Random();

        int firstNumber = 10 + random.nextInt(991); // Generates a random integer between 10 and 1000
        int secondNumber = 10 + random.nextInt(991); // Generates another random integer between 10 and 1000

        int result = firstNumber - secondNumber; // Calculates the difference between the two integers

        System.out.println("First Number: " + firstNumber);
        System.out.println("Second Number: " + secondNumber);
        System.out.println("Difference: " + result); // Prints the results
    }
}