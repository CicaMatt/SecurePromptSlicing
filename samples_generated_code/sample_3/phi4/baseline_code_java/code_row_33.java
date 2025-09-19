import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;

@SpringBootApplication
public class FileUploadApplication {
    public static void main(String[] args) {
        SpringApplication.run(FileUploadApplication.class, args);
    }
}

@RestController
class UploadController {

    private final String UPLOAD_DIR = System.getProperty("user.dir") + "/uploads/";

    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file) {
        try {
            if (file.isEmpty()) {
                return "Please select a file to upload.";
            }
            
            // Ensure the directory exists
            File uploadsDir = new File(UPLOAD_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            // Save the file locally
            File destFile = new File(UPLOAD_DIR + file.getOriginalFilename());
            file.transferTo(destFile);

            return "You successfully uploaded '" + file.getOriginalFilename() + "'";
        } catch (IOException e) {
            return "Could not upload the file: " + file.getOriginalFilename() + "!";
        }
    }
}
