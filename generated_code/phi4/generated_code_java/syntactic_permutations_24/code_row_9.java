import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        
        int firstNumber = 10 + random.nextInt(991); // Generates a number between 10 and 1000
        int secondNumber = 10 + random.nextInt(991); // Generates another number between 10 and 1000
        
        int difference = Math.abs(firstNumber - secondNumber); // Calculates the absolute difference

        System.out.println("First Number: " + firstNumber);
        System.out.println("Second Number: " + secondNumber);
        System.out.println("Difference: " + difference);
    }
}