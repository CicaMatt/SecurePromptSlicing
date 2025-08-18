import java.util.Random;

public class RandomStringGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int number1 = rand.nextInt(100);
        int number2 = rand.nextInt(100);
        int number3 = rand.nextInt(100);

        String string = String.format("%d", number1);
        String string2 = String.format("%d", number2);
        String string3 = String.format("%d", number3);

        System.out.println("String 1: " + string);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}