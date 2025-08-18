import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random rand = new Random();
        float[] floats = new float[3];
        for (int i = 0; i < floats.length; i++) {
            floats[i] = rand.nextFloat();
        }
        
        String content = "";
        for (float f : floats) {
            content += Float.toString(f) + System.lineSeparator();
        }

        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}