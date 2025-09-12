import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        int num1 = rand.nextInt(100);
        int num2 = rand.nextInt(100);
        int difference = Math.abs(num1 - num2);
        System.out.println("The difference is: " + difference);
    }
}