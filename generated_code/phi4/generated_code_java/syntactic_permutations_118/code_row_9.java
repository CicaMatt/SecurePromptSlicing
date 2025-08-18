import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            sb.append(randomFloat);
        }

        String resultString = sb.toString();

        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(resultString);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}