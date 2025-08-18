import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float numA = random.nextFloat();
        float numB = random.nextFloat();
        float numC = random.nextFloat();
        
        String str_a = convertFloatToString(numA);
        String str_b = convertFloatToString(numB);
        String str_c = convertFloatToString(numC);
    }
    
    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}