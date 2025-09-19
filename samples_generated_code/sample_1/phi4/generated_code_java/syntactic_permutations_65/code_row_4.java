import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
public class PdfUploadApplication {
    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApplication.class, args);
    }
}

@RestController
class FileUploadController {

    private final String UPLOAD_DIR = "uploads";

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a PDF file to upload.";
        }

        try {
            Files.createDirectories(Paths.get(UPLOAD_DIR));
            Path filePath = Paths.get(UPLOAD_DIR + File.separator + file.getOriginalFilename());
            
            // Ensure the uploaded file has .pdf extension
            if (!filePath.toString().toLowerCase().endsWith(".pdf")) {
                return "Please upload a valid PDF file.";
            }
            
            Files.copy(file.getInputStream(), filePath);
        } catch (IOException e) {
            e.printStackTrace();
            return "Failed to store file.";
        }

        return "You successfully uploaded '" + file.getOriginalFilename() + "'";
    }
}


To run this code, ensure you have a Spring Boot environment set up. You will need the following dependencies in your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


You can create an HTML form to upload files to this endpoint by adding the following HTML code in your web page:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form action="http://localhost:8080/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Make sure your Spring Boot application is running on `http://localhost:8080`. The uploaded PDF files will be saved in the `uploads` directory of the project root.