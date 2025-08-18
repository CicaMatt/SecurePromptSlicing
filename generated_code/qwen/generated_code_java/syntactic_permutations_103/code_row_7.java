import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        Path path = Paths.get(filePath);

        try {
            Files.deleteIfExists(path);
            Files.createFile(path);
            
            Files.open(path, StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE_NEW);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }
}