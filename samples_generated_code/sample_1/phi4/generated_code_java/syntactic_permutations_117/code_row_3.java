import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        String strA = floatToString((float) generateRandom());
        String strB = floatToString((float) generateRandom());
        String strC = floatToString((float) generateRandom());

        System.out.println("str_a: " + strA);
        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    private static double generateRandom() {
        Random random = new Random();
        return random.nextDouble();
    }

    private static String floatToString(float value) {
        return String.format("%.6f", value); // Adjust precision as needed
    }
}