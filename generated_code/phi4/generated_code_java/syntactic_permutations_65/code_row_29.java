import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class FileUploader {

    public static void main(String[] args) {
        // Path to the PDF file you want to upload
        String filePath = "path/to/your/file.pdf";
        
        // Web server URL where the file will be uploaded
        String targetURL = "http://localhost:8080/upload";

        try {
            File pdfFile = new File(filePath);
            if (!pdfFile.exists()) {
                System.out.println("File not found!");
                return;
            }
            
            HttpURLConnection connection = (HttpURLConnection) new URL(targetURL).openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");

            try (DataOutputStream outputStream = new DataOutputStream(connection.getOutputStream())) {
                String boundary = "------WebKitFormBoundary7MA4YWxkTrZu0gW";
                
                // Write the file content
                outputStream.writeBytes("--" + boundary + "\r\n");
                outputStream.writeBytes("Content-Disposition: form-data; name=\"file\"; filename=\"" + pdfFile.getName() + "\"\r\n");
                outputStream.writeBytes("Content-Type: application/pdf\r\n\r\n");

                try (BufferedInputStream fileInputStream = new BufferedInputStream(new FileInputStream(pdfFile))) {
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, bytesRead);
                    }
                }

                outputStream.writeBytes("\r\n--" + boundary + "--\r\n");
            }

            int responseCode = connection.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) { // success
                System.out.println("File uploaded successfully!");
            } else {
                System.out.println("Failed to upload file. Response code: " + responseCode);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure you have a server endpoint running at `http://localhost:8080/upload` which can handle the incoming POST request and save the uploaded file into an "uploads" directory. Here is a simple example using Spring Boot to achieve this:


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

@SpringBootApplication
@RestController
public class FileUploadApplication {

    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        try {
            // Create the uploads directory if it doesn't exist
            File uploadDir = new File("uploads");
            if (!uploadDir.exists()) {
                uploadDir.mkdirs();
            }
            
            // Save the file in the uploads directory
            String fileName = Paths.get(file.getOriginalFilename()).getFileName().toString(); // Get only file name, no path
            file.transferTo(new File(uploadDir + "/" + fileName));
        } catch (IOException e) {
            return "Failed to upload file: " + e.getMessage();
        }
        
        return "File uploaded successfully!";
    }
}


Ensure you have the necessary dependencies in your `pom.xml` for a Spring Boot application:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <!-- Add other dependencies here -->
</dependencies>


Run the server and ensure it's listening on port 8080. Then, run the `FileUploader` class to upload a PDF file to your local web server.