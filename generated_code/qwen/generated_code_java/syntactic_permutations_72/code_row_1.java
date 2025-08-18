import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(byte[] fileBytes, String filename) {
        Path uploadsDir = Paths.get("uploads");
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        Path filePath = uploadsDir.resolve(filename);
        try {
            Files.write(filePath, fileBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        byte[] exampleFileBytes = "Example content".getBytes();
        String exampleFilename = "example.txt";
        uploadFile(exampleFileBytes, exampleFilename);
    }
}