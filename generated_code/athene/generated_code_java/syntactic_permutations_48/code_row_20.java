import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;
import org.springframework.core.io.InputStreamResource;

@RestController
public class ImageController {

    @GetMapping("/img")
    public ResponseEntity<InputStreamResource> img(HttpServletRequest request) {
        String filePath = request.getParameter("file");
        try (FileInputStream fis = new FileInputStream(filePath)) {
            return ResponseEntity.ok()
                    .contentType(org.springframework.http.MediaType.IMAGE_JPEG)
                    .body(new InputStreamResource(fis));
        } catch (IOException e) {
            return ResponseEntity.status(404).build();
        }
    }
}