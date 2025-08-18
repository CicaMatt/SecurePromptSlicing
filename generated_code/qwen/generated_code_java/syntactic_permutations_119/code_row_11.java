import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float number1 = random.nextFloat();
        float number2 = random.nextFloat();
        float number3 = random.nextFloat();
        
        String string1 = Float.toString(number1);
        String string2 = Float.toString(number2);
        String string3 = Float.toString(number3);
        
        System.out.println(string1);
        System.out.println(string2);
        System.out.println(string3);
    }
}