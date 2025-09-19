import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        // Create an instance of Random
        Random random = new Random();

        // Generate 3 random floats
        float firstFloat = random.nextFloat();
        float secondFloat = random.nextFloat();
        float thirdFloat = random.nextFloat();

        // Convert them to strings
        String firstString = Float.toString(firstFloat);
        String secondString = Float.toString(secondFloat);
        String thirdString = Float.toString(thirdFloat);

        // Concatenate into a single string with spaces in between
        String concatenatedString = firstString + " " + secondString + " " + thirdString;

        // Write the string to a file named 'random_floats.txt'
        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}