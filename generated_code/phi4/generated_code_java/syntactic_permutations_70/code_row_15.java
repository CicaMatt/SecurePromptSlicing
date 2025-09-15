import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.UUID;

@SpringBootApplication
@RestController
public class FileUploadApplication {

    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }

    @PostMapping("/upload_file")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Failed to upload because the file is empty.";
        }
        
        try {
            // Create uploads directory if not exist
            Path uploadsDir = Paths.get("uploads");
            Files.createDirectories(uploadsDir);

            // Generate a unique filename
            String originalFilename = file.getOriginalFilename();
            String extension = originalFilename.substring(originalFilename.lastIndexOf("."));
            String newFileName = UUID.randomUUID().toString() + extension;

            // Save the file to uploads directory
            Path filePath = uploadsDir.resolve(newFileName);
            Files.copy(file.getInputStream(), filePath);

            return "File uploaded successfully: " + newFileName;
        } catch (IOException e) {
            return "Failed to upload file: " + e.getMessage();
        }
    }
}
