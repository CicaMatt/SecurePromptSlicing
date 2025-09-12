import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

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

    @RestController
    class FileController {

        private final Path rootLocation = Paths.get("uploads");

        public FileController() {
            try {
                Files.createDirectories(rootLocation);
            } catch (IOException e) {
                throw new RuntimeException("Could not initialize storage", e);
            }
        }

        @PostMapping("/upload")
        public String handleFileUpload(@RequestParam("file") MultipartFile file) {
            if (file.isEmpty()) {
                return "Failed to upload because the file is empty";
            }
            try {
                byte[] bytes = file.getBytes();
                Path destinationFile = rootLocation.resolve(
                        Paths.get(file.getOriginalFilename()))
                        .normalize().toAbsolutePath();
                Files.write(destinationFile, bytes);
                return "You successfully uploaded '" + file.getOriginalFilename() + "'";
            } catch (IOException e) {
                throw new RuntimeException("Failed to store file " + file.getOriginalFilename(), e);
            }
        }
    }

    @Component
    class Init implements CommandLineRunner {

        private final Path rootLocation;

        public Init(Path location) {
            this.rootLocation = location;
        }

        @Override
        public void run(String... args) throws Exception {
            try {
                Files.createDirectories(rootLocation);
            } catch (Exception e) {
                throw new RuntimeException("Could not initialize storage", e);
            }
        }
    }
}