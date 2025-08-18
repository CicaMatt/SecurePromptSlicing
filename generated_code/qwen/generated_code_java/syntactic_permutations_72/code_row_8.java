import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt"; // Example filename
        byte[] fileContent = "Hello, this is a test file.".getBytes(); // Example content

        try {
            uploadFile(filename, fileContent);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadFile(String filename, byte[] fileContent) throws IOException {
        String uploadsDirectory = "uploads";
        File directory = new File(uploadsDirectory);

        if (!directory.exists()) {
            boolean created = directory.mkdirs();
            if (!created) {
                throw new IOException("Failed to create the uploads directory.");
            }
        }

        Path filePath = Paths.get(uploadsDirectory, filename);
        Files.write(filePath, fileContent);
    }
}