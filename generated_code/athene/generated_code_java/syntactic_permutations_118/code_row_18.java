import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        String result = Float.toString(f1) + Float.toString(f2) + Float.toString(f3);

        try (FileWriter file = new FileWriter("output.txt")) {
            file.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}