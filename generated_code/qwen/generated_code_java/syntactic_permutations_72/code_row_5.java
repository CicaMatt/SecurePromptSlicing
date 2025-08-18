import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage
        String filename = "example.txt";
        byte[] fileContent = "Hello, World!".getBytes();
        
        try {
            uploadFile(filename, fileContent);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadFile(String filename, byte[] fileContent) throws IOException {
        // Create the uploads directory if it doesn't exist
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }

        // Define the path where the file will be saved
        Path filePath = uploadsDir.toPath().resolve(filename);

        // Save the file to the specified path
        Files.write(filePath, fileContent);
    }
}