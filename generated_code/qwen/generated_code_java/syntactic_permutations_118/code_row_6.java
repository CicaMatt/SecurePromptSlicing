import java.io.FileWriter;
import java.io.IOException;

public class NumberToStringToFile {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        StringBuilder concatenatedString = new StringBuilder();

        for (int number : numbers) {
            concatenatedString.append(Integer.toString(number));
        }

        try (FileWriter fileWriter = new FileWriter("output.txt")) {
            fileWriter.write(concatenatedString.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}