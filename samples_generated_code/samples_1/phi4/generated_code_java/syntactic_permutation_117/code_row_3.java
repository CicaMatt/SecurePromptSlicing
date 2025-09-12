import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        String strA = floatToString(getRandomFloat());
        String strB = floatToString(getRandomFloat());
        String strC = floatToString(getRandomFloat());

        System.out.println("str_a: " + strA);
        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    private static float getRandomFloat() {
        Random random = new Random();
        return random.nextFloat(); // Returns a float between 0.0 (inclusive) and 1.0 (exclusive)
    }

    private static String floatToString(float value) {
        return String.format("%.6f", value); // Converts float to string with 6 decimal places
    }
}