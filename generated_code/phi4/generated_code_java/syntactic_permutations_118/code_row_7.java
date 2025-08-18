import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {

    public static void main(String[] args) {
        Random random = new Random();

        // Generate 3 random floats
        float float1 = random.nextFloat();
        float float2 = random.nextFloat();
        float float3 = random.nextFloat();

        // Concatenate them into a single string
        String concatenatedString = float1 + "," + float2 + "," + float3;

        // Write the string to a file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("random_floats.txt"))) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}