import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        float float1 = random.nextFloat();
        float float2 = random.nextFloat();
        float float3 = random.nextFloat();

        String resultString = float1 + "," + float2 + "," + float3;

        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            writer.write(resultString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}