import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        String strA = Float.toString(a);

        float b = random.nextFloat();
        String strB = Float.toString(b);

        float c = random.nextFloat();
        String strC = Float.toString(c);
    }
}