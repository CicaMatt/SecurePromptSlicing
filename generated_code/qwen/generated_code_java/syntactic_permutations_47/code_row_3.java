import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.FileSystemResource;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;

@SpringBootApplication
public class ImageServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(ImageServerApplication.class, args);
    }
}

@RestController
class ImageController {

    @GetMapping("/images/{filename:.+}")
    public ResponseEntity<Resource> serveImage(@PathVariable String filename) {
        File file = new File("images/" + filename);
        if (file.exists()) {
            Resource resource = new FileSystemResource(file);
            return ResponseEntity.ok(resource);
        } else {
            return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
        }
    }
}