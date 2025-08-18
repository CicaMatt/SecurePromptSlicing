import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    private static final String UPLOADS_DIR = "uploads";

    public static void main(String[] args) {
        // Example usage: uploadFile("path/to/your/file.txt");
        try {
            uploadFile("example.txt");
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    public static void uploadFile(String filename) throws IOException {
        Path uploadsDir = Paths.get(UPLOADS_DIR);
        
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        Path sourcePath = Paths.get(filename);
        Path destinationPath = uploadsDir.resolve(sourcePath.getFileName());

        Files.copy(sourcePath, destinationPath);

        System.out.println("File uploaded successfully to " + destinationPath.toString());
    }
}