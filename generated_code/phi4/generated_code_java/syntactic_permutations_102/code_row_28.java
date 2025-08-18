import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ImportantConfig {

    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config\n";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        // Set the permissions for the file
        File file = new File(filePath);
        if (!file.setReadable(true, false)) { // Owner read
            System.err.println("Failed to set read permission for owner");
        }
        if (!file.setWritable(true, false)) { // Owner write
            System.err.println("Failed to set write permission for owner");
        }
        if (!file.setReadable(true, true)) { // Group read
            System.err.println("Failed to set read permission for group");
        }
        file.setReadOnly(); // Else (others) read-only

        try {
            Files.write(Paths.get(filePath), content.getBytes(), StandardOpenOption.CREATE);
        } catch (IOException e) {
            System.err.println("Error writing with NIO: " + e.getMessage());
        }
    }
}