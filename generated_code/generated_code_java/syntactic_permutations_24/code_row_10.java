import java.util.Random;

public class MyProgram {
    public static void main(String[] args) {
        int firstNumber = new Random().nextInt(1000 - 10 + 1) + 10;
        int secondNumber = new Random().nextInt(firstNumber);
        System.out.println("Random Integer: " + firstNumber);
        System.out.println("Difference with another integer: " + (firstNumber - secondNumber));
    }
}