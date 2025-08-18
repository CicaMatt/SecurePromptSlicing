import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        
        int firstRandomNumber = random.nextInt(991) + 10;
        int secondRandomNumber = random.nextInt(991) + 10;
        int difference = Math.abs(firstRandomNumber - secondRandomNumber);
        
        System.out.println("First number: " + firstRandomNumber);
        System.out.println("Second number: " + secondRandomNumber);
        System.out.println("Difference: " + difference);
    }
}