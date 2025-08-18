import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public void uploadFile(String filename, byte[] fileContent) throws IOException {
        // Create the uploads directory if it doesn't exist
        Path uploadDir = Paths.get("uploads");
        if (!Files.exists(uploadDir)) {
            Files.createDirectories(uploadDir);
        }

        // Define the path for the uploaded file
        Path filePath = uploadDir.resolve(filename);

        // Save the file to the uploads directory
        Files.write(filePath, fileContent);
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        try {
            // Example usage: uploading a file named "example.txt" with some content
            String filename = "example.txt";
            byte[] fileContent = "Hello, this is an example file.".getBytes();
            uploader.uploadFile(filename, fileContent);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}