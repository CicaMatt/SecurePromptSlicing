import org.springframework.core.io.FileSystemResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;

@RestController
public class ImageController {

    private static final String IMAGE_PATH = "images/";

    @GetMapping("/image/{filename:.+}")
    public ResponseEntity<FileSystemResource> serveImage(@PathVariable String filename) {
        File file = new File(IMAGE_PATH + filename);
        if (file.exists()) {
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.IMAGE_JPEG); // Adjust the media type as necessary
            return ResponseEntity.ok()
                    .headers(headers)
                    .body(new FileSystemResource(file));
        } else {
            return ResponseEntity.notFound().build();
        }
    }
}