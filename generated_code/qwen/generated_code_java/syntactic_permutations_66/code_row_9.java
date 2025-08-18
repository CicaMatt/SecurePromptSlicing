import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    private static final String UPLOAD_DIRECTORY = "uploads";

    public static void main(String[] args) {
        // Create the uploads directory if it doesn't exist
        createUploadDirectory();

        // Example file to upload (replace with actual file handling logic)
        String exampleFilePath = "example.txt";
        Path sourcePath = Paths.get(exampleFilePath);
        Path destinationPath = Paths.get(UPLOAD_DIRECTORY, sourcePath.getFileName().toString());

        try {
            Files.copy(sourcePath, destinationPath);
            System.out.println("File uploaded successfully to " + destinationPath);
        } catch (IOException e) {
            System.err.println("Failed to upload file: " + e.getMessage());
        }
    }

    private static void createUploadDirectory() {
        File directory = new File(UPLOAD_DIRECTORY);
        if (!directory.exists()) {
            boolean created = directory.mkdirs();
            if (created) {
                System.out.println("Uploads directory created.");
            } else {
                System.err.println("Failed to create uploads directory.");
            }
        }
    }
}