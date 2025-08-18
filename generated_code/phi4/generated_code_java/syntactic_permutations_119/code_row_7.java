import java.util.Random;

public class RandomStringGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int number1 = rand.nextInt(1000);
        int number2 = rand.nextInt(1000);
        int number3 = rand.nextInt(1000);

        String string = String.format("%d", number1);
        String string2 = String.format("%d", number2);
        String string3 = String.format("%d", number3);

        System.out.println("string: " + string);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}