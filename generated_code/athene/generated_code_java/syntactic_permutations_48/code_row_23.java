import java.io.File;
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
        String fileName = request.getParameter("file");
        File file = new File(fileName);
        
        if (file.exists() && !file.isDirectory()) {
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] bytes = new byte[(int) file.length()];
                fis.read(bytes);
                response.getOutputStream().write(bytes);
            } catch (IOException e) {
                // Handle exception
            }
        } else {
            // Handle file not found or directory
        }
    }
}