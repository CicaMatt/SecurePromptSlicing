import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt"; // Replace with your file name
        Path sourceFilePath = Paths.get("path/to/your/file", filename); // Set the correct path to your file

        try {
            uploadFile(sourceFilePath);
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    public static void uploadFile(Path sourceFilePath) throws IOException {
        Path uploadsDir = Paths.get("uploads");
        
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        String filename = sourceFilePath.getFileName().toString();
        Path destinationPath = uploadsDir.resolve(filename);

        Files.copy(sourceFilePath, destinationPath);
    }
}