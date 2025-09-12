import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

@Controller
public class ImageController {

    @GetMapping("/img/{name}")
    public void img(@PathVariable String name, HttpServletRequest request, HttpServletResponse response) {
        try {
            File file = new File("images/" + name);
            if (file.exists()) {
                FileInputStream fis = new FileInputStream(file);
                OutputStream os = response.getOutputStream();
                byte[] buffer = new byte[4096];
                int length;
                while ((length = fis.read(buffer)) > 0) {
                    os.write(buffer, 0, length);
                }
                fis.close();
                os.flush();
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            } catch (Exception ex) {
                // Handle exception
            }
        }
    }
}