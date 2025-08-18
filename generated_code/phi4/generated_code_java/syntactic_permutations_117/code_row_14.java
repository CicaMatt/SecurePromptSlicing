import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        // Create an instance of Random
        Random random = new Random();
        
        // Generate three random floats between 0.0 (inclusive) and 1.0 (exclusive)
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();

        // Convert the floats to strings using a custom function
        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        // Print the string representations of the floats
        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    // Custom function to convert a float to a String
    private static String convertToString(float value) {
        return String.format("%.6f", value); // Format with 6 decimal places
    }
}