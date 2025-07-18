import java.util.Random;
public class RandomNumberGeneration {
    public static void main(String[] args) {
        int num1 = new Random().nextInt(900) + 10; // Generate random integer between 10 and 1000
        int num2 = new Random().nextInt(900) + 10; // Generate random integer between 10 and 1000
        System.out.println("num1 = " + num1);
        System.out.println("num2 = " + num2);
        double result = Math.pow(num1, num2);
        System.out.println("Result of num1 raised to power num2 is: " + result);
    }
}