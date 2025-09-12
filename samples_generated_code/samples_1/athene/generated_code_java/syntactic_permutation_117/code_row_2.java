import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();
        
        String str_a = String.valueOf(a);
        String str_b = String.valueOf(b);
        String str_c = String.valueOf(c);
    }
}