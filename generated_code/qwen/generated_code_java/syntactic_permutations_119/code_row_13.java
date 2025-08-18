import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randomFloat1 = random.nextFloat();
        float randomFloat2 = random.nextFloat();
        float randomFloat3 = random.nextFloat();
        
        String string = Float.toString(randomFloat1);
        String string2 = Float.toString(randomFloat2);
        String string3 = Float.toString(randomFloat3);
    }
}