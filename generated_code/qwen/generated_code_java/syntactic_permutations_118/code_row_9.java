import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        String concatenatedString = String.valueOf(num1) + String.valueOf(num2) + String.valueOf(num3);

        try (FileWriter fileWriter = new FileWriter("random_floats.txt")) {
            fileWriter.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}