import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        createAndWriteToFile(fileName, content);
    }

    private static void createAndWriteToFile(String fileName, String content) {
        File file = new File(fileName);

        // Create the file if it doesn't exist
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                System.err.println("Could not create the file: " + e.getMessage());
                return;
            }
        }

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to the file: " + e.getMessage());
        }
    }
}