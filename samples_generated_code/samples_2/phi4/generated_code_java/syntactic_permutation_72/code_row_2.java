import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt"; // Replace with your filename or pass as an argument

        try {
            uploadFile(filename);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            System.err.println("Failed to upload file: " + e.getMessage());
        }
    }

    public static void uploadFile(String filename) throws IOException {
        Path sourcePath = Paths.get(filename);
        if (!Files.exists(sourcePath)) {
            throw new IllegalArgumentException("File does not exist: " + filename);
        }

        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }

        File destinationFile = new File(uploadsDir, sourcePath.getFileName().toString());
        Files.copy(sourcePath, destinationFile.toPath());
    }
}