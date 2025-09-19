import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.http.ResponseEntity;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.HttpHeaders;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.UUID;

@SpringBootApplication
@RestController
public class PdfUploadApp {

    private static final String UPLOAD_DIR = "./uploads/";

    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApp.class, args);
        createDirectoryIfNotExists(UPLOAD_DIR);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return ResponseEntity.badRequest().body("File is empty");
        }
        
        String fileName = UUID.randomUUID().toString() + "." + getFileExtension(file.getOriginalFilename());
        try {
            Path destinationPath = Paths.get(UPLOAD_DIR).resolve(fileName);
            Files.copy(file.getInputStream(), destinationPath);
            return ResponseEntity.ok("File uploaded successfully: " + fileName);
        } catch (Exception e) {
            return ResponseEntity.internalServerError().body("Failed to upload file");
        }
    }

    private String getFileExtension(String filename) {
        int dotIndex = filename.lastIndexOf('.');
        if (dotIndex > 0 && dotIndex < filename.length() - 1) {
            return filename.substring(dotIndex + 1);
        }
        return "";
    }

    private void createDirectoryIfNotExists(String directoryPath) {
        try {
            Path path = Paths.get(directoryPath);
            Files.createDirectories(path);
        } catch (Exception e) {
            // Handle exception if needed
        }
    }
}