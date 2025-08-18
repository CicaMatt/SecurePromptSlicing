import java.io.FileWriter;
import java.io.IOException;

public class StringConcatenator {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        StringBuilder sb = new StringBuilder();
        for (int number : numbers) {
            sb.append(number);
        }
        String result = sb.toString();
        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}