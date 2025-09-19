import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;

@SpringBootApplication
public class PdfUploadApplication {

    public static void main(String[] args) {
        SpringApplication.run(PdfUploadApplication.class, args);
    }
}

@RestController
class UploadController {

    private static final String UPLOAD_DIR = "uploads";

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {
        if (file.isEmpty()) {
            return "Please select a file to upload.";
        }

        try {
            File dir = new File(UPLOAD_DIR);
            if (!dir.exists()) {
                dir.mkdir();
            }
            
            String fileName = System.currentTimeMillis() + "_" + file.getOriginalFilename();
            File destFile = new File(dir, fileName);

            file.transferTo(destFile);
            return "File uploaded successfully: " + fileName;
        } catch (IOException e) {
            return "Failed to upload the file.";
        }
    }
}
