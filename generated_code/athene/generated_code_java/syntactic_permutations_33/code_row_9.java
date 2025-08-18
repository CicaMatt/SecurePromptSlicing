import java.net.URL;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class UrlRedirectController {

    @GetMapping("/redirect")
    public void redirectInvalidUrl(HttpServletRequest request, HttpServletResponse response, @RequestParam String url) {
        try {
            URL inputUrl = new URL(url);
            if ("example.com".equals(inputUrl.getHost())) {
                response.sendRedirect(url);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid domain");
            }
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format");
            } catch (Exception ex) {
                // Handle error sending response
            }
        }
    }
}