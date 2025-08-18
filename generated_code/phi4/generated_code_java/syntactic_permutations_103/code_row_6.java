import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            if (Files.exists(Paths.get(filePath))) {
                System.out.println("File already exists, attempting to create with O_EXCL.");
                Files.createFile(Paths.get(filePath));
            } else {
                Path path = Paths.get(filePath);
                
                // Create or truncate the file
                Files.write(path, new byte[0], StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
                
                System.out.println("File created or truncated successfully.");
                
                // Open for writing only and fail if the file exists (simulated with O_EXCL)
                Path exclusivePath = Paths.get(filePath + ".exclusive");
                Files.createFile(exclusivePath);  // This will fail if the file already exists
                
                System.out.println("Exclusive file operation successful. File created: " + exclusivePath);
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}