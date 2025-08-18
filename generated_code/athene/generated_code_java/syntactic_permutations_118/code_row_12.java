import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        String s1 = Float.toString(f1);
        String s2 = Float.toString(f2);
        String s3 = Float.toString(f3);

        String result = s1 + s2 + s3;

        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}