import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float randomA = rand.nextFloat();
        float randomB = rand.nextFloat();
        float randomC = rand.nextFloat();

        String str_a = convertToDecimalString(randomA);
        String str_b = convertToDecimalString(randomB);
        String str_c = convertToDecimalString(randomC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToDecimalString(float number) {
        return String.format("%.6f", number); // Adjust the precision as needed
    }
}