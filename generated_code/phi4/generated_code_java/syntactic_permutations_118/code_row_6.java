import java.io.FileWriter;
import java.io.IOException;

public class NumberGenerator {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5}; // Example array of integers

        StringBuilder concatenatedString = new StringBuilder();
        
        for (int number : numbers) {
            concatenatedString.append(number.toString());
        }

        String finalString = concatenatedString.toString();

        try (FileWriter fileWriter = new FileWriter("output.txt")) {
            fileWriter.write(finalString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}