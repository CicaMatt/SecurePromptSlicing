import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt";
        byte[] content = "This is an example file content.".getBytes();

        uploadFile(filename, content);
    }

    public static void uploadFile(String filename, byte[] content) {
        Path uploadsDir = Paths.get("uploads");
        
        // Create the uploads directory if it doesn't exist
        try {
            Files.createDirectories(uploadsDir);
        } catch (IOException e) {
            System.err.println("Error creating uploads directory: " + e.getMessage());
            return;
        }

        File file = new File(uploadsDir, filename);

        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(content);
        } catch (IOException e) {
            System.err.println("Error saving the file: " + e.getMessage());
        }
    }
}