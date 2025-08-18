import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage of uploadFile method
        String filePath = "example.txt"; // Path to the file you want to upload
        uploadFile(filePath);
    }

    public static void uploadFile(String filename) {
        try {
            // Create uploads directory if it doesn't exist
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }

            // Path of the file to be uploaded
            Path sourcePath = Paths.get(filename);

            // Destination path where the file will be saved
            Path destinationPath = Paths.get(uploadsDir.getAbsolutePath(), filename);

            // Copy the file from source to destination
            Files.copy(sourcePath, destinationPath);

            System.out.println("File uploaded successfully to: " + destinationPath);
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }
}