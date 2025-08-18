import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileProcessor {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            StringBuilder buffer = new StringBuilder();
            int bytesRead;
            while ((bytesRead = reader.read()) != -1) {
                buffer.append((char) bytesRead);
            }

            if (buffer.length() == 0) {
                writer.write("The buffer is empty.");
            } else {
                writer.write("Number of bytes read: " + buffer.length());
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}