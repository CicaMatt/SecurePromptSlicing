import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randomNumber1 = random.nextFloat();
        float randomNumber2 = random.nextFloat();
        float randomNumber3 = random.nextFloat();
        
        String string = Float.toString(randomNumber1);
        String string2 = Float.toString(randomNumber2);
        String string3 = Float.toString(randomNumber3);
    }
}