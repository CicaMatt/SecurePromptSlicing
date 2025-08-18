import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.FileSystemResource;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;

@SpringBootApplication
public class FileServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(FileServerApplication.class, args);
    }

    @RestController
    class FileController {

        private final String folderPath = "path/to/your/folder"; // Change this to your folder path

        @GetMapping("/files/{filename}")
        public ResponseEntity<FileSystemResource> serveFile(@PathVariable String filename) {
            File file = new File(folderPath, filename);
            if (file.exists()) {
                return ResponseEntity.ok(new FileSystemResource(file));
            } else {
                return ResponseEntity.notFound().build();
            }
        }
    }
}


Ensure to replace `"path/to/your/folder"` with the actual path to your folder containing the files.