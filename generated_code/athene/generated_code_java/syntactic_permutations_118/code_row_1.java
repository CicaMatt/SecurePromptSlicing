import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        String str1 = Float.toString(f1);
        String str2 = Float.toString(f2);
        String str3 = Float.toString(f3);

        String concatenatedString = str1 + str2 + str3;

        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}