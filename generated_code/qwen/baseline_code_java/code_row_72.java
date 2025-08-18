import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUpload {

    public static void main(String[] args) {
        // Example usage of uploadFile function
        try {
            uploadFile("example.txt", "This is an example file content.".getBytes());
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

        // Define the path to save the file
        Path filePath = Paths.get(uploadsDir.getAbsolutePath(), filename);

        // Save the file content to the specified path
        Files.write(filePath, fileContent);
    }
}