import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();

        // Generate 3 random floats between 0 and 1
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        // Convert them to strings
        String strF1 = Float.toString(f1);
        String strF2 = Float.toString(f2);
        String strF3 = Float.toString(f3);

        // Concatenate them into a single string separated by commas
        String concatenatedString = strF1 + "," + strF2 + "," + strF3;

        // Write the string to a file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("random_floats.txt"))) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}