import java.io.File;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.core.io.FileSystemResource;

@Controller
public class ImageController {

    @GetMapping("/img/{name}")
    public FileSystemResource img(@PathVariable String name, HttpServletRequest request, HttpServletResponse response) {
        File file = new File("path/to/images/" + name);
        return new FileSystemResource(file);
    }
}