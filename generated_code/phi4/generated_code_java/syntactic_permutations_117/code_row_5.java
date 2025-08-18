import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float randomA = rand.nextFloat();
        float randomB = rand.nextFloat();
        float randomC = rand.nextFloat();

        String str_a = convertToCustomString(randomA);
        String str_b = convertToCustomString(randomB);
        String str_c = convertToCustomString(randomC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static String convertToCustomString(float value) {
        return String.format("%.6f", value); // Example of a custom format
    }
}