import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        // Create an instance of Random
        Random random = new Random();

        // Generate 3 random floats and convert them to strings
        String float1 = Float.toString(random.nextFloat());
        String float2 = Float.toString(random.nextFloat());
        String float3 = Float.toString(random.nextFloat());

        // Concatenate the string representations with a newline character
        String data = float1 + "\n" + float2 + "\n" + float3;

        // Define the file path where the strings will be written
        String filePath = "random_floats.txt";

        // Use try-with-resources to ensure proper closure of BufferedWriter
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            // Write the concatenated string to the file
            writer.write(data);
        } catch (IOException e) {
            // Print an error message if something goes wrong during writing
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}