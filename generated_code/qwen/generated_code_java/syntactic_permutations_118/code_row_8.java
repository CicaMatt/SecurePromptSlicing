import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder floatsAsString = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            floatsAsString.append(randomFloat).append(" ");
        }

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(floatsAsString.toString().trim());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}