import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileWriter fileWriter = new FileWriter(new File(filePath), true)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}