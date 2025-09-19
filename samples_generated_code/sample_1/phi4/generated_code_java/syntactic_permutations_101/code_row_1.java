import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileWriter {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "important_config";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}