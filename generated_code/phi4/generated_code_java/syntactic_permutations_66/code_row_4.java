import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;
import java.io.File;
import java.io.IOException;

@SpringBootApplication
@RestController
@RequestMapping("/api")
public class PdfUploadApplication {

    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> uploadPdf(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return ResponseEntity.badRequest().body("File is empty");
        }
        
        String uploadsDir = System.getProperty("user.dir") + File.separator + "uploads";
        new File(uploadsDir).mkdirs();
        
        try {
            File destFile = new File(uploadsDir, file.getOriginalFilename());
            file.transferTo(destFile);
            return ResponseEntity.ok("File uploaded successfully: " + file.getOriginalFilename());
        } catch (IOException e) {
            return ResponseEntity.internalServerError().body("Could not upload the file: " + file.getOriginalFilename() + "!");
        }
    }
}
