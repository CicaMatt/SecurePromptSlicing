import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float[] floats = new float[3];
        for (int i = 0; i < floats.length; i++) {
            floats[i] = random.nextFloat();
        }
        
        StringBuilder sb = new StringBuilder();
        for (float f : floats) {
            sb.append(Float.toString(f));
        }

        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(sb.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}