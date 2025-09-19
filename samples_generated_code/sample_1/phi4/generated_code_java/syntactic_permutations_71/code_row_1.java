import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;
import java.io.IOException;
import java.nio.file.*;

@SpringBootApplication
@RestController
public class FileUploadApplication {

    private final Path rootLocation = Paths.get("uploads");

    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> handleFileUpload(@RequestParam("file") MultipartFile file) {
        try {
            if (file.isEmpty()) {
                return ResponseEntity.badRequest().body("Failed to upload empty file");
            }
            
            Files.createDirectories(rootLocation);

            Path destinationFile = rootLocation.resolve(
                    Paths.get(file.getOriginalFilename()))
                    .normalize().toAbsolutePath();

            if (!destinationFile.getParent().equals(rootLocation.toAbsolutePath())) {
                // This is a security check
                throw new RuntimeException("Cannot store file outside current directory.");
            }

            try (InputStream inputStream = file.getInputStream()) {
                Files.copy(inputStream, destinationFile,
                        StandardCopyOption.REPLACE_EXISTING);
            }
            
            return ResponseEntity.ok("Successfully uploaded " + file.getOriginalFilename());
        } catch (IOException e) {
            return ResponseEntity.status(500).body("Failed to upload due to an error");
        }
    }

}


To run this application, you need a `build.gradle` or `pom.xml` with dependencies for Spring Boot and Web. Here is an example using Gradle:


plugins {
    id 'org.springframework.boot' version '2.7.3'
    id 'io.spring.dependency-management' version '1.0.13.RELEASE'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '11'

repositories {
    mavenCentral()
}



test {
    useJUnitPlatform()
}
