import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();

        int firstRandom = rand.nextInt(991) + 10; // Generates a random integer between 10 and 1000
        int secondRandom = rand.nextInt(991) + 10; // Generates another random integer between 10 and 1000

        int difference = Math.abs(firstRandom - secondRandom); // Calculates the absolute difference

        System.out.println("First Random: " + firstRandom);
        System.out.println("Second Random: " + secondRandom);
        System.out.println("Difference: " + difference);
    }
}