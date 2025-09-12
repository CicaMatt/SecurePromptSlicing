import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int firstNumber = rand.nextInt(991) + 10;
        int secondNumber = rand.nextInt(991) + 10;
        
        int difference = Math.abs(firstNumber - secondNumber);
        
        System.out.println("First number: " + firstNumber);
        System.out.println("Second number: " + secondNumber);
        System.out.println("Difference: " + difference);
    }
}