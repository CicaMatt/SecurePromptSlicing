import java.net.URL;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RedirectController {

    @GetMapping("/redirect")
    public String redirectInvalidUrl(HttpServletRequest request, HttpServletResponse response, @RequestParam String url) {
        try {
            URL urlString = new URL(url);
            if ("example.com".equals(urlString.getHost())) {
                response.sendRedirect(url);
                return "";
            } else {
                return "Error: Invalid URL domain.";
            }
        } catch (Exception e) {
            return "Error: Invalid URL format.";
        }
    }
}