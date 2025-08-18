import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileWriter {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, false))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}