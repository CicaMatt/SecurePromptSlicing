import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();
        
        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);
    }
    
    private static String convertToString(float value) {
        return Float.toString(value);
    }
}