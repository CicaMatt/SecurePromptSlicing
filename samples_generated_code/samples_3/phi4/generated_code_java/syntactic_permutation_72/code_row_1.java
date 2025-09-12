import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.springframework.web.multipart.MultipartFile;

public class FileUploader {

    public void uploadFile(MultipartFile file) throws IOException {
        String uploadsDir = "uploads";
        
        // Create the directory if it doesn't exist
        Path dirPath = Paths.get(uploadsDir);
        if (!Files.exists(dirPath)) {
            Files.createDirectories(dirPath);
        }
        
        // Save the file in the uploads directory
        Path filePath = dirPath.resolve(file.getOriginalFilename());
        Files.write(filePath, file.getBytes());
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        MultipartFile mockFile; // Assume this is populated appropriately

        try {
            uploader.uploadFile(mockFile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}