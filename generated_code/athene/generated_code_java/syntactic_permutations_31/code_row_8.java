import java.net.URL;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RedirectController {

    @GetMapping("/redirect")
    public void redirectUrl(@RequestParam String url, HttpServletRequest request, HttpServletResponse response) throws Exception {
        URL parsedUrl = new URL(url);
        String domain = parsedUrl.getHost();
        
        if ("example.com".equals(domain)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}