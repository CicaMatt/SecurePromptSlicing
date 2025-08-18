import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int firstNumber = random.nextInt(991) + 10;
        int secondNumber = random.nextInt(991) + 10;
        int difference = Math.abs(firstNumber - secondNumber);
        System.out.println("First Number: " + firstNumber);
        System.out.println("Second Number: " + secondNumber);
        System.out.println("Difference: " + difference);
    }
}