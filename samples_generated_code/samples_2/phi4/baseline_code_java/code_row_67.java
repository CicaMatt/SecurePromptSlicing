import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        try {
            uploadFile("example.txt", "Hello, World!".getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadFile(String filename, byte[] content) throws IOException {
        Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
        if (!Files.exists(uploadsDir)) {
            Files.createDirectory(uploadsDir);
        }

        Path filePath = uploadsDir.resolve(filename);
        Files.write(filePath, content);

        System.out.println("File uploaded to: " + filePath.toString());
    }
}