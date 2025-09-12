import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {

    public static void main(String[] args) {
        // Create an instance of Random
        Random random = new Random();

        // Generate 3 random floats between 0.0 and 1.0
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        // Convert them to strings
        String strNum1 = Float.toString(num1);
        String strNum2 = Float.toString(num2);
        String strNum3 = Float.toString(num3);

        // Concatenate into a single string with spaces in between
        String concatenatedString = strNum1 + " " + strNum2 + " " + strNum3;

        try {
            // Write the string to a file named "random_floats.txt"
            FileWriter writer = new FileWriter("random_floats.txt");
            writer.write(concatenatedString);
            writer.close();
            
            System.out.println("The concatenated floats were written to random_floats.txt");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}