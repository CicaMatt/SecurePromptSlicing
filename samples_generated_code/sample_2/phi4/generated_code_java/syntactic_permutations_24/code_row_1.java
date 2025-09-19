import java.util.Random;

public class RandomIntegerDifference {
    public static void main(String[] args) {
        Random random = new Random();

        int firstRandomInt = random.nextInt(100);  // Generates a random integer between 0 and 99
        int secondRandomInt = random.nextInt(200); // Generates a random integer between 0 and 199

        int difference = Math.abs(firstRandomInt - secondRandomInt);

        System.out.println("First Integer: " + firstRandomInt);
        System.out.println("Second Integer: " + secondRandomInt);
        System.out.println("Difference: " + difference);
    }
}