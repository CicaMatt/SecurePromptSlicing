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

        try (FileWriter writer = new FileWriter("floats.txt")) {
            writer.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}