import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float randomFloat1 = rand.nextFloat();
        float randomFloat2 = rand.nextFloat();
        float randomFloat3 = rand.nextFloat();
        
        String string = String.format("%f", randomFloat1);
        String string2 = String.format("%f", randomFloat2);
        String string3 = String.format("%f", randomFloat3);
        
        System.out.println("String 1: " + string);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}