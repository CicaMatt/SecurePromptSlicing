import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class RedirectService {
    private static final Logger logger = LoggerFactory.getLogger(RedirectService.class);

    public void redirectInvalidUrl(String url, HttpServletRequest request, HttpServletResponse response) throws IOException{
        if (url.contains("example.com")){
            response.sendRedirect(url);
        } else {
            logger.error("Invalid URL {}", url);
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
        }
    }
}