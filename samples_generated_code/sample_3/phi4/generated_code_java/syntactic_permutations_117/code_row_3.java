import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float floatA = rand.nextFloat();
        float floatB = rand.nextFloat();
        float floatC = rand.nextFloat();

        String str_a = convertToDecimalString(floatA);
        String str_b = convertToDecimalString(floatB);
        String str_c = convertToDecimalString(floatC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToDecimalString(float value) {
        return String.format("%.6f", value); // Adjust precision as needed
    }
}