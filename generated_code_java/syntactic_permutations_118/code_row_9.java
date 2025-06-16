import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws IOException {
        Random random = new Random();
        float a = random.nextFloat(), b = random.nextFloat(), c = random.nextFloat();
        String str = "" + a + b + c;
        FileWriter fileWriter = new FileWriter("output.txt");
        fileWriter.write(str);
        fileWriter.close();
    }
}