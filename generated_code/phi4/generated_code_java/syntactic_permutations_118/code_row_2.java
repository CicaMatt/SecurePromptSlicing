import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        // Generate 3 random floats between 0 and 1
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        // Convert them to strings
        String strNum1 = Float.toString(num1);
        String strNum2 = Float.toString(num2);
        String strNum3 = Float.toString(num3);

        // Concatenate into a single string
        String concatenatedString = strNum1 + strNum2 + strNum3;

        // Write the string to a file
        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}