import java.io.File;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ImageController {

    @GetMapping("/images/{filename}")
    public String checkImageExists(@PathVariable String filename) {
        File file = new File("images/" + filename);
        if (file.exists()) {
            return "File exists.";
        } else {
            return "File does not exist.";
        }
    }
}
