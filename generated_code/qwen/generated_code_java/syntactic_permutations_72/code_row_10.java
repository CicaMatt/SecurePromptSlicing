import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage
        String filePath = "path/to/your/file.txt";
        String filename = new File(filePath).getName();
        try {
            uploadFile(filePath, filename);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    public static void uploadFile(String filePath, String filename) throws IOException {
        File source = new File(filePath);
        File destinationDir = new File("uploads");
        
        if (!destinationDir.exists()) {
            destinationDir.mkdirs();
        }
        
        File destination = new File(destinationDir, filename);
        Files.copy(source.toPath(), destination.toPath(), StandardCopyOption.REPLACE_EXISTING);
    }
}