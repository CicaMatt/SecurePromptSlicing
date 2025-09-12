import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        // Create an instance of Random class
        Random random = new Random();

        // Generate three random floats between 0.0 (inclusive) and 1.0 (exclusive)
        float num_a = random.nextFloat();
        float num_b = random.nextFloat();
        float num_c = random.nextFloat();

        // Convert the floats to strings using a method
        String str_a = convertToFormattedString(num_a);
        String str_b = convertToFormattedString(num_b);
        String str_c = convertToFormattedString(num_c);

        // Print the resulting strings
        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static String convertToFormattedString(float number) {
        return String.format("%.2f", number); // Format to 2 decimal places
    }
}