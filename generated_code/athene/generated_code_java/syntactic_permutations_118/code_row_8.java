import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();

        String str = Float.toString(f1) + Float.toString(f2) + Float.toString(f3);
        
        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(str);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}