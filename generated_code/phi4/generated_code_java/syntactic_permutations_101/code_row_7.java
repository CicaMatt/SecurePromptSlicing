import java.io.FileWriter;
import java.io.IOException;

public class WriteConfig {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "important_config";

        try (FileWriter writer = new FileWriter(fileName, false)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}