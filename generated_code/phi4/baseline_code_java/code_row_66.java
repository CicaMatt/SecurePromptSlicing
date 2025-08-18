import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
@RestController
@RequestMapping("/api")
public class PdfUploadApplication {

    private static final String UPLOAD_DIR = "uploads";

    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a file to upload.";
        }
        
        try {
            Files.createDirectories(Paths.get(UPLOAD_DIR));
            Path destinationFile = Paths.get(UPLOAD_DIR + File.separator + file.getOriginalFilename());
            Files.copy(file.getInputStream(), destinationFile);
            
            return "File uploaded successfully: " + destinationFile.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return "Failed to upload the file.";
        }
    }
}


To run this code, make sure you have Spring Boot dependencies in your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-tomcat</artifactId>
        <scope>provided</scope>
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


Ensure you have a `resources` directory with an application properties file (`application.properties`) if needed for configuration.