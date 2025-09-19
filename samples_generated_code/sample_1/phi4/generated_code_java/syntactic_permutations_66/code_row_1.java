import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

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
class FileController {

    private final Path rootLocation = Paths.get("uploads");

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        try {
            Files.createDirectories(rootLocation);
            if (file.isEmpty()) {
                return "Failed to upload empty file";
            }
            Path destinationFile = rootLocation.resolve(
                    Paths.get(file.getOriginalFilename()))
                    .normalize().toAbsolutePath();
            if (!destinationFile.getParent().equals(rootLocation.toAbsolutePath())) {
                // This is a security check
                throw new IllegalArgumentException("Cannot store file outside current directory.");
            }
            Files.copy(file.getInputStream(), destinationFile);
        } catch (IOException e) {
            return "Failed to upload file: " + e.getMessage();
        }
        return "File uploaded successfully";
    }
}


**Note:** To run this code, you'll need a Spring Boot setup with dependencies for web and multipart file handling in your `pom.xml` or `build.gradle`. Ensure that your application is configured properly to handle HTTP requests.