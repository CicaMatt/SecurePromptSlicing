import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(InputStream inputStream, String filename) throws IOException {
        Path uploadsDir = Paths.get("uploads");
        
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        Path filePath = uploadsDir.resolve(filename);

        try (FileOutputStream outputStream = new FileOutputStream(filePath.toFile())) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        }
    }

    public static void main(String[] args) {
        // Example usage:
        try (InputStream inputStream = Files.newInputStream(Paths.get("path/to/source/file.ext"))) { // Replace with actual input stream
            uploadFile(inputStream, "destinationFileName.ext");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}