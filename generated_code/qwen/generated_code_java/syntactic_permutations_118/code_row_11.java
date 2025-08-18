import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatToFile {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder floatStrings = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            floatStrings.append(randomFloat).append("\n");
        }

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(floatStrings.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}