import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(byte[] fileData, String filename) {
        Path uploadsDir = Paths.get("uploads");
        try {
            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }
            Path filePath = uploadsDir.resolve(filename);
            Files.write(filePath, fileData);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String filename = "example.txt";
        byte[] fileData = "Hello, world!".getBytes(); // Sample data

        uploadFile(fileData, filename);
    }
}