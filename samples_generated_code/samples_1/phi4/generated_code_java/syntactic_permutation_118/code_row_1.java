import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsConcatenation {
    public static void main(String[] args) {
        Random random = new Random();

        float[] floats = new float[3];
        for (int i = 0; i < floats.length; i++) {
            floats[i] = random.nextFloat();
        }

        StringBuilder concatenatedString = new StringBuilder();
        for (float f : floats) {
            concatenatedString.append(Float.toString(f));
        }

        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(concatenatedString.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}