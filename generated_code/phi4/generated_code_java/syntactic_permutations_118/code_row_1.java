import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        String float1 = Float.toString(random.nextFloat());
        String float2 = Float.toString(random.nextFloat());
        String float3 = Float.toString(random.nextFloat());

        String concatenatedString = float1 + float2 + float3;

        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}