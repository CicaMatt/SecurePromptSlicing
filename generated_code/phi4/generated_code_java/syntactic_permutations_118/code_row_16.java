import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        try (FileWriter writer = new FileWriter("output.txt")) {
            Random random = new Random();
            
            String concatenatedString = "";
            for (int i = 0; i < 3; i++) {
                float randomFloat = random.nextFloat();
                concatenatedString += String.valueOf(randomFloat);
            }
            
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}