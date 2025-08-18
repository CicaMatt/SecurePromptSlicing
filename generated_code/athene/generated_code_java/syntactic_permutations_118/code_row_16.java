import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float[] floats = new float[3];
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < floats.length; i++) {
            floats[i] = random.nextFloat();
            sb.append(floats[i]).append(",");
        }

        String result = sb.toString();
        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}