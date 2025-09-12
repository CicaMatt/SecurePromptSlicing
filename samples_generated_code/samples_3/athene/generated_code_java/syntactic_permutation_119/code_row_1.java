import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();
        String string = Float.toString(rand.nextFloat());
        String string2 = Float.toString(rand.nextFloat());
        String string3 = Float.toString(rand.nextFloat());
    }
}