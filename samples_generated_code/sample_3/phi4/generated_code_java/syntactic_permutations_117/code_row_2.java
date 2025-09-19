import java.util.Random;

public class RandomFloatConverter {
    public static void main(String[] args) {
        // Create a Random object instance
        Random random = new Random();

        // Generate three random floats
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();

        // Convert the floats to strings and store in variables
        String str_a = Float.toString(a);
        String str_b = Float.toString(b);
        String str_c = Float.toString(c);

        // Output the results
        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }
}