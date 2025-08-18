import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsConcatenation {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder concatenatedString = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            String floatAsString = Float.toString(randomFloat);
            concatenatedString.append(floatAsString);
        }

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(concatenatedString.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}