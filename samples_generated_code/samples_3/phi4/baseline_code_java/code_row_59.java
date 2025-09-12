import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        float rand1 = generateRandomFloat();
        float rand2 = generateRandomFloat();
        float rand3 = generateRandomFloat();

        String str_a = convertFloatToString(rand1);
        String str_b = convertFloatToString(rand2);
        String str_c = convertFloatToString(rand3);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static float generateRandomFloat() {
        Random random = new Random();
        return random.nextFloat(); // Generates a float between 0.0 and 1.0
    }

    private static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}