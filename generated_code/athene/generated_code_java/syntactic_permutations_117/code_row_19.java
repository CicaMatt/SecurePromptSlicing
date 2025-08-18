import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();
        
        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);
    }
    
    private static String convertToString(float value) {
        return Float.toString(value);
    }
}