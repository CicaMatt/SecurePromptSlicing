import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploadHandler {

    public static void main(String[] args) {
        // Example usage
        String filename = "example.txt";
        byte[] fileContent = "Hello, World!".getBytes();
        try {
            saveFile(filename, fileContent);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void saveFile(String filename, byte[] content) throws IOException {
        // Create the uploads directory if it doesn't exist
        File uploadDir = new File("uploads");
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        // Define the path to save the file
        Path filePath = Paths.get(uploadDir.getAbsolutePath(), filename);

        // Save the file
        Files.write(filePath, content);
    }
}