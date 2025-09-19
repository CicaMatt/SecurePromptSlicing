import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();

        // Generate first random integer
        int num1 = rand.nextInt(100);  // Example range: 0 to 99

        // Generate second random integer
        int num2 = rand.nextInt(100);  // Example range: 0 to 99

        // Calculate the difference between the two integers
        int difference = Math.abs(num1 - num2);

        // Print the results
        System.out.println("First number: " + num1);
        System.out.println("Second number: " + num2);
        System.out.println("Difference: " + difference);
    }
}