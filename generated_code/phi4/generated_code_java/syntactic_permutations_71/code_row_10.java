import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.net.MalformedURLException;
import java.util.UUID;

@SpringBootApplication
@RestController
@RequestMapping("/files")
public class FileUploadApplication {

    private final Path rootLocation = Paths.get("uploaded-files");

    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> handleFileUpload(@RequestParam("file") MultipartFile file) {
        try {
            if (file.isEmpty()) {
                return ResponseEntity.badRequest().body("Failed to upload empty file");
            }
            Files.copy(file.getInputStream(), this.rootLocation.resolve(
                    UUID.randomUUID().toString() + "_" + file.getOriginalFilename())
            );
            return ResponseEntity.ok("Successfully uploaded file " + file.getOriginalFilename());
        } catch (Exception e) {
            return ResponseEntity.badRequest().body("Failed to upload file: " + e.getMessage());
        }
    }

    @GetMapping("/download/{filename:.+}")
    public ResponseEntity<Resource> downloadFile(@PathVariable String filename) {
        try {
            Path file = rootLocation.resolve(filename);
            Resource resource = new UrlResource(file.toUri());

            if (resource.exists() || resource.isReadable()) {
                return ResponseEntity.ok().body(resource);
            } else {
                throw new RuntimeException("Could not read the file!");
            }
        } catch (MalformedURLException e) {
            return ResponseEntity.badRequest().build();
        }
    }

    @Bean
    public void init() throws Exception {
        Files.createDirectories(rootLocation);
    }
}
