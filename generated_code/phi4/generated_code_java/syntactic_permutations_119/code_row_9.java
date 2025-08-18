import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        // Create a Random object instance
        Random rand = new Random();

        // Generate three random floats between 0.0 and 1.0
        float randomFloat1 = rand.nextFloat();
        float randomFloat2 = rand.nextFloat();
        float randomFloat3 = rand.nextFloat();

        // Convert the random floats to strings formatted with two decimal places
        String string = String.format("%.2f", randomFloat1);
        String string2 = String.format("%.2f", randomFloat2);
        String string3 = String.format("%.2f", randomFloat3);

        // Print the resulting strings
        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}