import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int firstRandomInt = 10 + rand.nextInt(991); // Generates a random integer between 10 and 1000
        int secondRandomInt = rand.nextInt(1001);     // Generates another random integer between 0 and 1000
        int difference = Math.abs(firstRandomInt - secondRandomInt);
        
        System.out.println("First Integer: " + firstRandomInt);
        System.out.println("Second Integer: " + secondRandomInt);
        System.out.println("Difference: " + difference);
    }
}