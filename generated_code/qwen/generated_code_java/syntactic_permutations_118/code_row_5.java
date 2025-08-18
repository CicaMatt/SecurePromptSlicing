import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Integer number = 123;
        Double decimal = 456.789;
        String text = "Hello, World!";

        String concatenatedString = number.toString() + decimal.toString() + text;

        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}