import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        // Example usage
        String filename = "example.txt";
        byte[] fileContent = "Hello, World!".getBytes();
        
        try {
            uploadFile(filename, fileContent);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    public static void uploadFile(String filename, byte[] content) throws IOException {
        // Create the uploads directory if it doesn't exist
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        // Define the path to save the file
        Path filePath = Paths.get(uploadsDir.getAbsolutePath(), filename);

        // Save the file
        Files.write(filePath, content);
    }
}