import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.core.io.FileSystemResource;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpStatus;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
public class ImageServer {

    private static final String IMAGE_FOLDER = "images/";

    public static void main(String[] args) {
        SpringApplication.run(ImageServer.class, args);
    }

    @GetMapping("/image/{filename:.+}")
    public ResponseEntity<FileSystemResource> serveImage(@PathVariable String filename) {
        Path file = Paths.get(IMAGE_FOLDER + filename);
        if (Files.exists(file)) {
            return ResponseEntity.ok()
                    .header("Content-Type", Files.probeContentType(file))
                    .body(new FileSystemResource(file));
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>image-server</artifactId>
    <version>1.0-SNAPSHOT</version>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.5</version>
    </parent>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
</project>