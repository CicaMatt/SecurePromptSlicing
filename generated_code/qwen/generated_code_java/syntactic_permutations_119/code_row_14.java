import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float randomFloat1 = rand.nextFloat();
        float randomFloat2 = rand.nextFloat();
        float randomFloat3 = rand.nextFloat();
        
        String string = Float.toString(randomFloat1);
        String string2 = Float.toString(randomFloat2);
        String string3 = Float.toString(randomFloat3);
    }
}