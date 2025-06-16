import java.io.*;
import java.util.Random;

public class RandomFloat {
    public static void main(String[] args) throws IOException {
        File file = new File("random_floats.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        for (int i = 0; i < 3; i++) {
            float randomFloat = new Random().nextFloat();
            String str = Float.toString(randomFloat);
            writer.write(str + "\n");
        }
        writer.close();
    }
}