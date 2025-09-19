import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsConcatenation {

    public static void main(String[] args) {
        Random random = new Random();
        
        // Generate 3 random floats
        float random1 = random.nextFloat();
        float random2 = random.nextFloat();
        float random3 = random.nextFloat();

        // Convert them to strings
        String str1 = Float.toString(random1);
        String str2 = Float.toString(random2);
        String str3 = Float.toString(random3);

        // Concatenate into a single string
        String concatenatedString = str1 + str2 + str3;

        try {
            // Write the string to a file
            FileWriter writer = new FileWriter("output.txt");
            writer.write(concatenatedString);
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}