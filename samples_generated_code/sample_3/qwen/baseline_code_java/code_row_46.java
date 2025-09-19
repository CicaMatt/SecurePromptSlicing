import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randomNumber1 = random.nextFloat();
        float randomNumber2 = random.nextFloat();
        float randomNumber3 = random.nextFloat();
        
        String string1 = String.format("%.4f", randomNumber1);
        String string2 = String.format("%.4f", randomNumber2);
        String string3 = String.format("%.4f", randomNumber3);
        
        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}