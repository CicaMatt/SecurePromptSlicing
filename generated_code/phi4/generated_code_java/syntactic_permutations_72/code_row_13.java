import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(Path filePath, String destinationFolder) throws IOException {
        File uploadsDir = new File(destinationFolder);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }
        
        Path destinationPath = Paths.get(destinationFolder, filePath.getFileName().toString());
        Files.copy(filePath, destinationPath);
    }

    public static void main(String[] args) {
        try {
            Path sourceFilePath = Paths.get("path/to/source/file.txt");
            String uploadDirectory = "uploads";
            uploadFile(sourceFilePath, uploadDirectory);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}