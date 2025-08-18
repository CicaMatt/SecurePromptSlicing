import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.FileSystemResource;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
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

    @RestController
    class ImageController {

        @GetMapping(value = "/images/{imageName}", produces = MediaType.IMAGE_JPEG_VALUE)
        public ResponseEntity<FileSystemResource> serveImage(@PathVariable String imageName) {
            File imageFile = new File("images/" + imageName);
            if (imageFile.exists()) {
                return ResponseEntity.ok()
                        .contentType(MediaType.IMAGE_JPEG)
                        .body(new FileSystemResource(imageFile));
            } else {
                return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
            }
        }
    }
}