import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage
        String filePath = "path/to/your/file.txt";
        uploadFile(filePath);
    }

    public static void uploadFile(String filePath) {
        try {
            // Create the uploads directory if it doesn't exist
            Path uploadsDir = Paths.get("uploads");
            Files.createDirectories(uploadsDir);

            // Get the file name from the path
            File file = new File(filePath);
            String fileName = file.getName();

            // Define the destination path
            Path destinationPath = uploadsDir.resolve(fileName);

            // Copy the file to the uploads directory
            Files.copy(file.toPath(), destinationPath);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}