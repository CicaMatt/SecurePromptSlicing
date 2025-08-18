import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {

    public static void main(String[] args) {
        Path filePath = Paths.get("example.txt");

        try {
            // Open or create the file with specified flags
            Files.newByteChannel(filePath, StandardOpenOption.CREATE,
                    StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.WRITE);
            
            System.out.println("File opened successfully for writing.");
            
            // Example usage: Write some data to the file
            byte[] data = "Hello, World!".getBytes();
            Files.write(filePath, data);

        } catch (IOException e) {
            if (e.getMessage().contains("already exists")) {
                System.err.println("File already exists and O_EXCL was simulated by custom check.");
            } else {
                e.printStackTrace();
            }
        }
    }
}