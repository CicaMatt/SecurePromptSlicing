import java.net.URL;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UrlRedirectController {

    @GetMapping("/redirect")
    public void redirectInvalidUrl(HttpServletRequest request, HttpServletResponse response, @RequestParam String url) throws Exception {
        URL urlObject = new URL(url);
        if ("example.com".equals(urlObject.getHost())) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid domain");
        }
    }
}