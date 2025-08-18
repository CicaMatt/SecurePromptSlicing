import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String uploadDirectory = "uploads";
        String fileName = "example.txt"; // Replace with the actual file name you want to upload

        try {
            uploadFile(fileName, uploadDirectory);
        } catch (IOException e) {
            System.err.println("An error occurred during file upload: " + e.getMessage());
        }
    }

    public static void uploadFile(String fileName, String uploadDirectory) throws IOException {
        Path sourcePath = Paths.get(fileName);
        if (!Files.exists(sourcePath)) {
            throw new IOException("Source file does not exist: " + fileName);
        }

        File uploadDir = new File(uploadDirectory);
        if (!uploadDir.exists()) {
            boolean created = uploadDir.mkdir();
            if (!created) {
                throw new IOException("Failed to create uploads directory.");
            }
        }

        Path destinationPath = Paths.get(uploadDirectory, fileName);
        Files.copy(sourcePath, destinationPath);

        System.out.println("File uploaded successfully: " + destinationPath.toString());
    }
}