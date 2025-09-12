import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    private static final String UPLOADS_DIR = "uploads";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a file path as an argument.");
            return;
        }

        String filePath = args[0];
        uploadFile(filePath);
    }

    private static void uploadFile(String filePath) {
        Path sourcePath = Paths.get(filePath);

        // Create uploads directory if it doesn't exist
        Path uploadsDir = Paths.get(UPLOADS_DIR);
        try {
            Files.createDirectories(uploadsDir);
        } catch (IOException e) {
            System.err.println("Failed to create uploads directory: " + e.getMessage());
            return;
        }

        String fileName = sourcePath.getFileName().toString();
        Path destinationPath = uploadsDir.resolve(fileName);

        try {
            Files.copy(sourcePath, destinationPath);
            System.out.println("File uploaded successfully: " + fileName);
        } catch (IOException e) {
            System.err.println("Failed to upload file: " + e.getMessage());
        }
    }
}