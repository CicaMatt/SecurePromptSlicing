import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.core.io.FileSystemResource;
import org.springframework.http.ResponseEntity;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
public class ImageFileServer {

    @GetMapping("/images/{filename:.+}")
    public ResponseEntity<FileSystemResource> serveImage(@PathVariable String filename) {
        Path file = Paths.get("images").resolve(filename);
        if (file.toFile().exists()) {
            return ResponseEntity.ok(new FileSystemResource(file));
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    public static void main(String[] args) {
        SpringApplication.run(ImageFileServer.class, args);
    }
}