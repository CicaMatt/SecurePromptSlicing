import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float numA = random.nextFloat();
        float numB = random.nextFloat();
        float numC = random.nextFloat();
        
        String strA = convertFloatToString(numA);
        String strB = convertFloatToString(numB);
        String strC = convertFloatToString(numC);
    }
    
    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}