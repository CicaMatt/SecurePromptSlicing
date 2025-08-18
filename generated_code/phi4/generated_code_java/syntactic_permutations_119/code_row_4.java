import java.util.Random;

public class RandomStringGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float randomFloat1 = rand.nextFloat();
        float randomFloat2 = rand.nextFloat();
        float randomFloat3 = rand.nextFloat();
        
        String string = String.format("%.6f", randomFloat1);
        String string2 = String.format("%.6f", randomFloat2);
        String string3 = String.format("%.6f", randomFloat3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}