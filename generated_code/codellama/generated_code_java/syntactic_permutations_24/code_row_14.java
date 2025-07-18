import java.util.Random;
public class Main {
    public static void main(String[] args) {
        Random r = new Random();
        int number1 = r.nextInt(900) + 100;
        int number2 = r.nextInt(900) + 100;
        int diff = Math.abs(number1 - number2);
        System.out.println("Difference between the two integers: " + diff);
    }
}