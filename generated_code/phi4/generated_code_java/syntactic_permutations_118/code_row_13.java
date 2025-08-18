import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        // Create a Random object to generate random floats
        Random rand = new Random();
        
        // Generate 3 random floats between 0.0 and 1.0
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        // Convert the floats to strings
        String str1 = Float.toString(num1);
        String str2 = Float.toString(num2);
        String str3 = Float.toString(num3);

        // Concatenate the strings
        String concatenatedString = str1 + str2 + str3;

        // Write the concatenated string to a file
        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}