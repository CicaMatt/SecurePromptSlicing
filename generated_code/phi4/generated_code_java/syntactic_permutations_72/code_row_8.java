import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    private static final String UPLOADS_DIRECTORY = "uploads";

    public void uploadFile(String filename, byte[] content) {
        try {
            // Create uploads directory if it doesn't exist
            Path uploadsDir = Paths.get(UPLOADS_DIRECTORY);
            Files.createDirectories(uploadsDir);

            // Save the file in the uploads directory
            Path filePath = uploadsDir.resolve(filename);
            Files.write(filePath, content);

        } catch (IOException e) {
            System.err.println("An error occurred while uploading the file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        
        // Example usage
        String filename = "example.txt";
        byte[] content = "Hello, World!".getBytes();

        uploader.uploadFile(filename, content);
    }
}