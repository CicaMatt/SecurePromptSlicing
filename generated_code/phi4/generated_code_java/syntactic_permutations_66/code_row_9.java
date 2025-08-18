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

@SpringBootApplication
@RestController
public class FileUploadApplication {

    private static final String UPLOAD_DIR = "uploads";

    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
        
        // Ensure the uploads directory exists
        Path uploadPath = Paths.get(UPLOAD_DIR);
        if (!Files.exists(uploadPath)) {
            try {
                Files.createDirectories(uploadPath);
            } catch (IOException e) {
                System.out.println("Could not create uploads directory: " + e.getMessage());
            }
        }
    }

    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a file to upload.";
        }

        try {
            Path targetLocation = Paths.get(UPLOAD_DIR).resolve(
                    Paths.get(file.getOriginalFilename()))
                    .normalize().toAbsolutePath();

            // Check if the file's name contains invalid path characters
            if (!targetLocation.getParent().equals(Paths.get(UPLOAD_DIR).toAbsolutePath())) {
                throw new IOException("Cannot save file outside of uploads directory.");
            }

            Files.copy(file.getInputStream(), targetLocation);
        } catch (IOException e) {
            return "Could not store file " + file.getOriginalFilename() + ". Please try again!";
        }
        
        return "You successfully uploaded '" + file.getOriginalFilename() + "'";
    }
}


**Note:** To run this code, ensure you have a Spring Boot application set up with the necessary dependencies (e.g., `spring-boot-starter-web`). This example assumes you're using Spring Boot to handle web requests.