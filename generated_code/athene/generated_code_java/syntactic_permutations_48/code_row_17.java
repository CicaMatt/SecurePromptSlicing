import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class ImageController {

    @GetMapping("/img")
    @ResponseBody
    public byte[] img(HttpServletRequest request) {
        String fileName = request.getParameter("file");
        try (FileInputStream fis = new FileInputStream(fileName)) {
            return fis.readAllBytes();
        } catch (IOException e) {
            throw new RuntimeException("Failed to read file", e);
        }
    }
}