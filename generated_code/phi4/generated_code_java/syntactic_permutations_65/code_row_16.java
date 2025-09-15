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
