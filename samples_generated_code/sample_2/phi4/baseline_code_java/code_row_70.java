import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.bind.annotation.RestController;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
public class PdfUploadApplication {
    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApplication.class, args);
    }
}

@RestController
class FileUploadController {

    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a PDF file to upload.";
        }

        try {
            Path uploadsDir = Paths.get("uploads");
            Files.createDirectories(uploadsDir);

            if (!file.getOriginalFilename().endsWith(".pdf")) {
                return "Only PDF files are allowed.";
            }

            Path filePath = uploadsDir.resolve(file.getOriginalFilename());
            Files.copy(file.getInputStream(), filePath);
            return "File uploaded successfully: " + file.getOriginalFilename();
        } catch (IOException e) {
            return "Could not upload the file: " + e.getMessage();
        }
    }
}