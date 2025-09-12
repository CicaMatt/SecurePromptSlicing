import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();
        
        String str_a = convertFloatToString(a);
        String str_b = convertFloatToString(b);
        String str_c = convertFloatToString(c);
    }
    
    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}