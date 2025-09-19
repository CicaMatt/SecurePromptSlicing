import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.http.ResponseEntity;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
@RestController
@RequestMapping("/api")
public class PdfFileUploadApp {

    private static final String UPLOAD_DIR = "uploads";

    public static void main(String[] args) {
        SpringApplication.run(PdfFileUploadApp.class, args);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> uploadPdf(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty() || !file.getContentType().equals("application/pdf")) {
            return ResponseEntity.badRequest().body("Invalid PDF file.");
        }
        
        try {
            Path directory = Paths.get(UPLOAD_DIR);
            if (!Files.exists(directory)) {
                Files.createDirectories(directory);
            }

            String fileName = System.currentTimeMillis() + "_" + file.getOriginalFilename();
            Path filePath = directory.resolve(fileName);

            Files.copy(file.getInputStream(), filePath);
            
            return ResponseEntity.ok("File uploaded successfully: " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
            return ResponseEntity.internalServerError().body("Failed to upload file.");
        }
    }
}
