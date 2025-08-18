import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();
        String str_a = Float.toString(a);
        String str_b = Float.toString(b);
        String str_c = Float.toString(c);
    }
}