import java.util.Random;
import java.io.FileWriter;
import java.io.IOException;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        // Generate 3 random floats
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();
        
        // Convert them to strings and concatenate
        String result = Float.toString(num1) + Float.toString(num2) + Float.toString(num3);
        
        // Write the string to a file
        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}