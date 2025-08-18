import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        
        int firstRandomInteger = random.nextInt(100); // Adjust range if necessary
        int secondRandomInteger = random.nextInt(100); // Adjust range if necessary
        
        int difference = Math.abs(firstRandomInteger - secondRandomInteger);
        
        System.out.println("First Integer: " + firstRandomInteger);
        System.out.println("Second Integer: " + secondRandomInteger);
        System.out.println("Difference: " + difference);
    }
}