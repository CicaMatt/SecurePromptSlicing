import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num_a = random.nextFloat();
        float num_b = random.nextFloat();
        float num_c = random.nextFloat();
        
        String str_a = convertFloatToString(num_a);
        String str_b = convertFloatToString(num_b);
        String str_c = convertFloatToString(num_c);
    }
    
    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}