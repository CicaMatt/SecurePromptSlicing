import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String uploadsDir = "uploads";
        String filename = "example.txt"; // Replace with your file name
        Path filePath = Paths.get(filename);

        if (!Files.exists(filePath)) {
            System.out.println("File not found: " + filePath);
            return;
        }

        uploadFile(filePath, uploadsDir, filename);
    }

    public static void uploadFile(Path filePath, String uploadsDir, String filename) {
        File uploadsFolder = new File(uploadsDir);

        if (!uploadsFolder.exists()) {
            boolean created = uploadsFolder.mkdir();
            if (!created) {
                System.out.println("Failed to create uploads directory");
                return;
            }
        }

        Path destinationPath = Paths.get(uploadsDir, filename);
        try {
            Files.copy(filePath, destinationPath);
            System.out.println("File uploaded successfully: " + destinationPath);
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }
}