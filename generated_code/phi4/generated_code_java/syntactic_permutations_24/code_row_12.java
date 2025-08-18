import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        
        int firstRandomInteger = random.nextInt(100); // Generates a random integer between 0 (inclusive) and 100 (exclusive)
        int secondRandomInteger = random.nextInt(200); // Generates a random integer between 0 (inclusive) and 200 (exclusive)
        int difference = Math.abs(firstRandomInteger - secondRandomInteger);
        
        System.out.println("First Random Integer: " + firstRandomInteger);
        System.out.println("Second Random Integer: " + secondRandomInteger);
        System.out.println("Difference: " + difference);
    }
}