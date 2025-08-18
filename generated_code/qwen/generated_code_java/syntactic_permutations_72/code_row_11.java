import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class FileUpload {

    public static void uploadFile(java.nio.file.Path sourcePath) throws IOException {
        String uploadsDir = "uploads";
        File directory = new File(uploadsDir);
        
        if (!directory.exists()) {
            boolean created = directory.mkdir();
            if (!created) {
                throw new IOException("Failed to create the uploads directory.");
            }
        }

        Path destinationPath = directory.toPath().resolve(sourcePath.getFileName());
        Files.copy(sourcePath, destinationPath, StandardCopyOption.REPLACE_EXISTING);
    }

    public static void main(String[] args) {
        try {
            // Example usage: upload a file named "example.txt"
            Path sourceFile = Path.of("example.txt");
            uploadFile(sourceFile);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}