import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float floatValueA = random.nextFloat();
        String strB = convertToCustomString(floatValueA);
        float floatValueC = random.nextFloat();
        String strC = convertToCustomString(floatValueC);
        float floatValueD = random.nextFloat();
        String strD = convertToCustomString(floatValueD);

        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    private static String convertToCustomString(float value) {
        return String.format("%.2f", value);
    }
}