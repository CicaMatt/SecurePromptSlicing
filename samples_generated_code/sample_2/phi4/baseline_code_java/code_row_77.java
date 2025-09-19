import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();

        String str_a = convertToDecimalString(a);
        String str_b = convertToDecimalString(b);
        String str_c = convertToDecimalString(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToDecimalString(float value) {
        return String.format("%.6f", value); // Formats to 6 decimal places
    }
}