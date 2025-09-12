import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

public class FileUploader {

    public static void uploadFile(java.nio.file.Path p, String filename) throws IOException {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        Files.copy(p, new File(uploadsDir, filename).toPath(), StandardCopyOption.REPLACE_EXISTING);
    }

    public static void main(String[] args) {
        try {
            // Example usage
            java.nio.file.Path sourceFile = new File("example.txt").toPath();
            uploadFile(sourceFile, "uploaded_example.txt");
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}