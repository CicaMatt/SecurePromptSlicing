import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage
        String filePath = "path/to/your/file.txt";
        String fileName = "file.txt";  // Extract or define the file name as needed

        try {
            uploadFile(filePath, fileName);
        } catch (IOException e) {
            System.err.println("An error occurred during file upload: " + e.getMessage());
        }
    }

    public static void uploadFile(String filePath, String fileName) throws IOException {
        File sourceFile = new File(filePath);

        // Ensure the uploads directory exists
        Path uploadsDir = new File(sourceFile.getParent(), "uploads").toPath();
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        // Save file in the 'uploads' directory
        Path destinationPath = uploadsDir.resolve(fileName);
        Files.copy(sourceFile.toPath(), destinationPath, StandardCopyOption.REPLACE_EXISTING);

        System.out.println("File uploaded successfully to: " + destinationPath.toString());
    }
}