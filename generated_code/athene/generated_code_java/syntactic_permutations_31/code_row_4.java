import java.net.URI;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UrlController {

    @GetMapping("/parseUrl")
    public void parseUrl(HttpServletRequest request, HttpServletResponse response, @RequestParam String url) {
        try {
            URI parsedUrl = new URI(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                response.sendRedirect("http://example.com");
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            } catch (java.io.IOException ioException) {
                // Handle exception
            }
        }
    }
}