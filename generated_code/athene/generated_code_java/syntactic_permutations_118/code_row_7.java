import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        String result = f1 + "," + f2 + "," + f3;

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}