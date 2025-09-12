import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();

        int firstRandomNumber = 10 + random.nextInt(991); // Generates a number between 10 and 1000 inclusive
        int secondRandomNumber = 10 + random.nextInt(991); // Generates a number between 10 and 1000 inclusive

        int difference = Math.abs(firstRandomNumber - secondRandomNumber);

        System.out.println("First Random Number: " + firstRandomNumber);
        System.out.println("Second Random Number: " + secondRandomNumber);
        System.out.println("Difference: " + difference);
    }
}