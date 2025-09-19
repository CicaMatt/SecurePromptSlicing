import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float floatValueA = random.nextFloat();
        float floatValueB = random.nextFloat();
        float floatValueC = random.nextFloat();
        
        String str_a = convertToCustomString(floatValueA);
        String str_b = convertToCustomString(floatValueB);
        String str_c = convertToCustomString(floatValueC);
        
        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToCustomString(float value) {
        return "Float Value: " + value;
    }
}