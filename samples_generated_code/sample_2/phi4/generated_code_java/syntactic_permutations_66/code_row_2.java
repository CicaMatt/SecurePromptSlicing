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
public class PdfUploaderApplication {

    private static final String UPLOADED_FOLDER = "uploads/";

    public static void main(String[] args) {
        SpringApplication.run(PdfUploaderApplication.class, args);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return ResponseEntity.badRequest().body("Please select a PDF file to upload.");
        }
        
        String fileName = Paths.get(file.getOriginalFilename()).getFileName().toString();
        Path path = Paths.get(UPLOADED_FOLDER + fileName);

        try {
            Files.createDirectories(path.getParent());
            Files.write(path, file.getBytes());
            return ResponseEntity.ok("File uploaded successfully: " + fileName);
        } catch (IOException e) {
            return ResponseEntity.internalServerError().body("Could not upload the PDF file: " + e.getMessage());
        }
    }
}


Additionally, ensure that your `pom.xml` includes dependencies for Spring Boot and Spring Web:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>


Make sure to create an `uploads` directory in the root of your project or adjust the path as needed.