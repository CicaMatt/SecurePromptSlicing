import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        int num1 = 10 + rand.nextInt(991);
        int num2 = 10 + rand.nextInt(991);
        int difference = Math.abs(num1 - num2);
        System.out.println("The difference between " + num1 + " and " + num2 + " is: " + difference);
    }
}