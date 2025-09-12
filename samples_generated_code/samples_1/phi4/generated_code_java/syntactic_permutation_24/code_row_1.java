import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        
        int firstRandomInteger = random.nextInt(100); // Generates a random integer between 0 and 99
        int secondRandomInteger = random.nextInt(100); // Generates another random integer between 0 and 99
        
        int difference = Math.abs(firstRandomInteger - secondRandomInteger); // Calculates the absolute difference between the two integers
        
        System.out.println("First Random Integer: " + firstRandomInteger);
        System.out.println("Second Random Integer: " + secondRandomInteger);
        System.out.println("Difference: " + difference);
    }
}