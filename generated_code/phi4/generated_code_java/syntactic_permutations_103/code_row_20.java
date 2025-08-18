import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Path.of("example.txt");

        try {
            Files.write(filePath, new byte[0], 
                StandardOpenOption.CREATE, 
                StandardOpenOption.TRUNCATE_EXISTING, 
                StandardOpenOption.WRITE);
            
            System.out.println("File created or truncated successfully.");
            
            // Attempting to open with O_EXCL flag
            try {
                Files.createFile(filePath, StandardOpenOption.EXCLUSIVE);
            } catch (IOException e) {
                System.out.println("File already exists, as expected with O_EXCL.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}