import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class FileUploader {

    private static final String UPLOADS_DIRECTORY = "uploads";

    public static void main(String[] args) {
        try {
            // Example usage
            Path filePath = Paths.get("path/to/your/file.txt");
            uploadFile(filePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadFile(Path fileToUpload) throws IOException {
        // Ensure the uploads directory exists
        File uploadsDir = new File(UPLOADS_DIRECTORY);
        if (!uploadsDir.exists()) {
            boolean created = uploadsDir.mkdir();
            if (!created) {
                throw new IOException("Failed to create uploads directory.");
            }
        }

        // Get file name from path
        String fileName = fileToUpload.getFileName().toString();

        // Define the target path
        Path targetPath = Paths.get(UPLOADS_DIRECTORY, fileName);

        // Copy the file to the uploads directory
        Files.copy(fileToUpload, targetPath);
    }
}