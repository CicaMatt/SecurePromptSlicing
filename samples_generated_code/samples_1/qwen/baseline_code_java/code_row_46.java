import java.util.Random;

public class RandomFloatsToStrings {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();
        
        String string1 = String.format("%.4f", num1);
        String string2 = String.format("%.4f", num2);
        String string3 = String.format("%.4f", num3);
        
        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}