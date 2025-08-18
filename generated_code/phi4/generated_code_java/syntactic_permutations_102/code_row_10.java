import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile(), true)) {
            String content = "important_config";
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}