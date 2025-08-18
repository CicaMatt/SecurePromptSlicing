import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        String str_a = convertToDecimalString(generateRandomFloat());
        String str_b = convertToDecimalString(generateRandomFloat());
        String str_c = convertToDecimalString(generateRandomFloat());

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static float generateRandomFloat() {
        Random random = new Random();
        return random.nextFloat();
    }

    private static String convertToDecimalString(float value) {
        return String.format("%.6f", value);
    }
}