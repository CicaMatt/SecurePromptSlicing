import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();
        String str_a = String.valueOf(a);
        String str_b = String.valueOf(b);
        String str_c = String.valueOf(c);
    }
}