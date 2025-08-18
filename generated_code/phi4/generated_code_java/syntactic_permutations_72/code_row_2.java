import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String fileName = "example.txt";
        byte[] content = "Sample file content".getBytes();

        try {
            uploadFile(fileName, content);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void uploadFile(String fileName, byte[] content) throws IOException {
        String uploadsDir = "uploads";
        
        File dir = new File(uploadsDir);
        if (!dir.exists()) {
            dir.mkdir();
        }

        Path filePath = Paths.get(uploadsDir, fileName);
        Files.write(filePath, content);

        System.out.println("File uploaded successfully to: " + filePath.toString());
    }
}