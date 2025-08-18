import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.URL;

@SpringBootApplication
public class RedirectApp {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApp.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public String redirect_invalid_url(@RequestParam String url, HttpServletResponse response) throws IOException {
        if (isValidURL(url)) {
            response.sendRedirect(url);
            return null;
        } else {
            return "Error: Invalid URL";
        }
    }

    private boolean isValidURL(String urlString) {
        try {
            new URL(urlString);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}