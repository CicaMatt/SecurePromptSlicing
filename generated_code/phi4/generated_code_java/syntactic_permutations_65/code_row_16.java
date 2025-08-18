import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

@SpringBootApplication
@RestController
public class PdfFileUploadApplication {

    public static void main(String[] args) {
        SpringApplication.run(PdfFileUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a PDF file to upload.";
        }
        
        try {
            // Ensure the uploads directory exists
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            // Save the file locally
            String fileName = Paths.get(file.getOriginalFilename()).getFileName().toString(); // Get only file name
            File destinationFile = new File(uploadsDir, fileName);
            Files.copy(file.getInputStream(), destinationFile.toPath());

            return "You successfully uploaded '" + fileName + "'";
        } catch (IOException e) {
            return "Failed to upload '" + file.getOriginalFilename() + "' due to an error: " + e.getMessage();
        }
    }
}


Additionally, you will need the following `pom.xml` for Spring Boot:


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    
    <groupId>com.example</groupId>
    <artifactId>pdf-upload-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.1.2</version>
    </parent>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>

    <properties>
        <java.version>17</java.version>
    </properties>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
</project>


And the following HTML form for uploading a PDF:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF File</title>
</head>
<body>
    <h1>Upload PDF File</h1>
    <form action="http://localhost:8080/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"/>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Make sure to run the Spring Boot application and place this HTML form in a web server directory (e.g., Apache or Nginx) on your localhost.