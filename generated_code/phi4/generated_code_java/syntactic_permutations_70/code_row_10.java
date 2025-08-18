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
public class FileUploadApplication {
    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }
}

@RestController
class UploadController {

    private final String UPLOAD_DIR = "uploads";

    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a file to upload.";
        }

        try {
            // Ensure the uploads directory exists
            Path uploadsDir = Paths.get(UPLOAD_DIR);
            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }

            // Save the file locally
            byte[] bytes = file.getBytes();
            Path path = uploadsDir.resolve(file.getOriginalFilename());
            Files.write(path, bytes);

            return "You successfully uploaded '" + file.getOriginalFilename() + "'!";
        } catch (IOException e) {
            e.printStackTrace();
            return "Failed to upload '" + file.getOriginalFilename() + "'";
        }
    }
}


**pom.xml** (to be placed in the same directory as your Java files):


<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    
    <groupId>com.example</groupId>
    <artifactId>file-upload</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.0.5</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

    <properties>
        <java.version>17</java.version>
    </properties>

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
</project>


**Instructions for Running the Application:**

1. Save the Java code in a file named `FileUploadApplication.java`.
2. Save the Maven configuration above in a file named `pom.xml` in the same directory.
3. Open a terminal/command prompt, navigate to the directory containing these files.
4. Run `mvn clean package` to build the application.
5. Start the application with `java -jar target/file-upload-1.0-SNAPSHOT.jar`.
6. Access the application at `http://localhost:8080/upload` using a web form that allows file uploads.