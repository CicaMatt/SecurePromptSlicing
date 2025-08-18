import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random rand = new Random();
        
        // Generate 3 random floats between 0 (inclusive) and 1 (exclusive)
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        // Convert to strings
        String strNum1 = Float.toString(num1);
        String strNum2 = Float.toString(num2);
        String strNum3 = Float.toString(num3);

        // Concatenate into a single string
        String concatenatedString = strNum1 + "," + strNum2 + "," + strNum3;

        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            // Write the string to a file
            writer.write(concatenatedString);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}