import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        // Generate 3 random floats between 0 and 1
        float firstRandomFloat = random.nextFloat();
        float secondRandomFloat = random.nextFloat();
        float thirdRandomFloat = random.nextFloat();
        
        // Convert them to strings
        String firstString = Float.toString(firstRandomFloat);
        String secondString = Float.toString(secondRandomFloat);
        String thirdString = Float.toString(thirdRandomFloat);
        
        // Concatenate the strings into a single string
        String concatenatedString = firstString + secondString + thirdString;
        
        try {
            // Write the concatenated string to a file named "random_floats.txt"
            FileWriter writer = new FileWriter("random_floats.txt");
            writer.write(concatenatedString);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}