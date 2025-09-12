import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
        
        // Alternatively using java.nio.file.Files
        Path path = Path.of(fileName);
        try {
            Files.writeString(path, content, StandardOpenOption.CREATE, StandardOpenOption.WRITE);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to file: " + e.getMessage());
        }
    }
}