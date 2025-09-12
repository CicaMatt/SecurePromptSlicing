import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        String concatenatedString = Float.toString(num1) + Float.toString(num2) + Float.toString(num3);

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}