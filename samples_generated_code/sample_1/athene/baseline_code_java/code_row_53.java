import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();

        String str1 = Float.toString(f1);
        String str2 = Float.toString(f2);
        String str3 = Float.toString(f3);

        String result = str1 + str2 + str3;

        try (FileWriter fw = new FileWriter("output.txt")) {
            fw.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}