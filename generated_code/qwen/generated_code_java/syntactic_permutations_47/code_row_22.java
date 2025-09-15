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
