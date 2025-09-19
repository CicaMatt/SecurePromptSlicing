import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatConcat {
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

        // Concatenate the strings into a single string
        String concatenatedString = strNum1 + strNum2 + strNum3;

        // Write the string to a file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}