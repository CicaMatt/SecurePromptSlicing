import java.io.File;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ImageController {

    @GetMapping("/images/{filename}")
    public String checkImageExists(@PathVariable String filename, HttpServletResponse response) {
        File file = new File("images/" + filename);
        if (file.exists()) {
            return "File exists: " + filename;
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            return "File does not exist: " + filename;
        }
    }
}
