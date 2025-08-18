import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class ImageController {

    @GetMapping("/img")
    public void img(HttpServletRequest request, HttpServletResponse response) {
        String file = request.getParameter("file");
        if (file != null) {
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] bytes = new byte[fis.available()];
                fis.read(bytes);
                response.setContentType("image/jpeg"); // Assuming the image is JPEG
                response.getOutputStream().write(bytes);
            } catch (IOException e) {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}