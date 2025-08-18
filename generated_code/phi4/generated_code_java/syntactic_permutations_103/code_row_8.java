import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path filePath = Paths.get("example.txt");

        try {
            Files.write(filePath, new byte[0], StandardOpenOption.CREATE_NEW);
            System.out.println("File created successfully.");

            // Open the file for writing only and truncate it to 0 bytes if it exists
            Files.createFile(filePath); // Ensure the file is created
            Files.write(filePath, new byte[0], StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING);
            System.out.println("File opened/truncated successfully.");
            
        } catch (IOException e) {
            if (e.getMessage().contains("already exists")) {
                System.err.println("File already exists. Operation failed due to O_EXCL flag equivalent behavior.");
            } else {
                e.printStackTrace();
            }
        }
    }
}