import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int num1 = 10 + rand.nextInt(991); // Generates a random integer between 10 and 1000.
        int num2 = 10 + rand.nextInt(991); // Generates another random integer between 10 and 1000.

        int difference = Math.abs(num1 - num2); // Calculates the absolute difference between the two integers.

        System.out.println("First number: " + num1);
        System.out.println("Second number: " + num2);
        System.out.println("Difference: " + difference);
    }
}