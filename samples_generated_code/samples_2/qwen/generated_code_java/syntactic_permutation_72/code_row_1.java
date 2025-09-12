import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(String filename, byte[] fileContent) {
        String uploadDirectory = "uploads" + File.separator;
        Path directoryPath = Paths.get(uploadDirectory);

        try {
            if (!Files.exists(directoryPath)) {
                Files.createDirectories(directoryPath);
            }
            Path filePath = Paths.get(uploadDirectory, filename);
            Files.write(filePath, fileContent);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String filename = "example.txt";
        byte[] fileContent = "Hello, this is a test file.".getBytes();
        uploadFile(filename, fileContent);
    }
}