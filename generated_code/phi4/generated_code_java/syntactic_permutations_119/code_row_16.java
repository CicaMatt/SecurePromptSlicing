import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float number1 = rand.nextFloat();
        float number2 = rand.nextFloat();
        float number3 = rand.nextFloat();

        String string1 = String.format("%.4f", number1);
        String string2 = String.format("%.4f", number2);
        String string3 = String.format("%.4f", number3);

        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}