import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {

    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randFloat = random.nextFloat(); // Generates a random float between 0.0 and 1.0
            String floatStr = Float.toString(randFloat);
            result.append(floatStr).append(",");
        }

        result.setLength(result.length() - 1); // Remove the last comma

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(result.toString());
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}