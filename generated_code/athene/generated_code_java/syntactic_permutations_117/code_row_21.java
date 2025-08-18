import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();
        
        String str_a = convertFloatToString(a);
        String str_b = convertFloatToString(b);
        String str_c = convertFloatToString(c);
    }
    
    private static String convertFloatToString(float f) {
        return String.valueOf(f);
    }
}