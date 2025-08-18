import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();
        
        String str_a = convertTostring(a);
        String str_b = convertTostring(b);
        String str_c = convertTostring(c);
    }
    
    public static String convertTostring(float value) {
        return Float.toString(value);
    }
}