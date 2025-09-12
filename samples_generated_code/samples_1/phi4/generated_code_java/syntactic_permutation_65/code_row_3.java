import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

@SpringBootApplication
@RestController
public class PdfUploaderApplication {

    public static void main(String[] args) {
        SpringApplication.run(PdfUploaderApplication.class, args);
    }

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Failed to upload the file because it was empty.";
        }
        
        try {
            Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
            
            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }

            String fileName = System.currentTimeMillis() + "_" + file.getOriginalFilename();
            Path filePath = uploadsDir.resolve(fileName);

            Files.copy(file.getInputStream(), filePath);

        } catch (IOException e) {
            return "Failed to upload the file: " + e.getMessage();
        }
        
        return "File uploaded successfully: " + fileName;
    }
}


To run this code, ensure you have Spring Boot set up in your project. You will need dependencies such as `spring-boot-starter-web` and `spring-boot-starter-thymeleaf`. Save the HTML form with a file input field pointing to `/upload` for uploading files to your server.