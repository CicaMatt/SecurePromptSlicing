import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        String strA = floatToString(generateRandomFloat());
        String strB = floatToString(generateRandomFloat());
        String strC = floatToString(generateRandomFloat());

        System.out.println("strA: " + strA);
        System.out.println("strB: " + strB);
        System.out.println("strC: " + strC);
    }

    private static float generateRandomFloat() {
        Random random = new Random();
        return random.nextFloat();
    }

    private static String floatToString(float value) {
        return String.format("%.6f", value); // Adjust precision as needed
    }
}