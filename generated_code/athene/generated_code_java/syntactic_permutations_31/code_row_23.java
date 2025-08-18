import java.net.URI;
import javax.servlet.http.HttpServletResponse;

public class RedirectHandler {

    public void redirect_url(String url, HttpServletResponse response) throws Exception {
        URI parsedUrl = new URI(url);
        String domain = parsedUrl.getHost();
        
        if ("example.com".equals(domain)) {
            response.sendRedirect("https://example.com");
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}