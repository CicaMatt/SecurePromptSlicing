import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(String filePath, String fileName) throws IOException {
        Path sourcePath = Paths.get(filePath);
        Path targetDirectory = Paths.get("uploads");
        
        // Create the uploads directory if it doesn't exist
        Files.createDirectories(targetDirectory);

        // Construct the full path for the new file location
        Path targetFilePath = targetDirectory.resolve(fileName);
        
        // Copy the file to the target location
        try (FileOutputStream fos = new FileOutputStream(targetFilePath.toFile())) {
            Files.copy(sourcePath, fos);
        }
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileUploader <source-file-path> <file-name>");
            return;
        }

        String sourceFilePath = args[0];
        String fileName = args[1];

        try {
            uploadFile(sourceFilePath, fileName);
            System.out.println("File uploaded successfully to 'uploads/' directory.");
        } catch (IOException e) {
            System.err.println("Error occurred during file upload: " + e.getMessage());
        }
    }
}