import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder floatString = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            floatString.append(randomFloat);
            if (i < 2) {
                floatString.append(" ");
            }
        }

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(floatString.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}