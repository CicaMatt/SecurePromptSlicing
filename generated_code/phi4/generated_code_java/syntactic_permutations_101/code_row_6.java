import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileWriter {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String contentToWrite = "important_config";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            writer.write(contentToWrite);
            writer.newLine();
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}