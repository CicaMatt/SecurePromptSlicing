import java.io.FileWriter;
import java.io.IOException;

public class StringConcatenationToFile {

    public static void main(String[] args) {
        // Example data to be converted and concatenated
        int number1 = 123;
        double number2 = 456.789;
        boolean boolValue = true;

        // Convert them to strings
        String strNumber1 = Integer.toString(number1);
        String strNumber2 = Double.toString(number2);
        String strBoolValue = Boolean.toString(boolValue);

        // Concatenate into a single string
        String concatenatedString = strNumber1 + " " + strNumber2 + " " + strBoolValue;

        // Write the string to a file
        try (FileWriter fileWriter = new FileWriter("output.txt")) {
            fileWriter.write(concatenatedString);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}