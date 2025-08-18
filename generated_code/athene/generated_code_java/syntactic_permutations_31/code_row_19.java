import java.net.URL;
import javax.servlet.http.HttpServletResponse;

public class RedirectHandler {
    public void redirect_url(String url, HttpServletResponse response) throws Exception {
        URL parsedUrl = new URL(url);
        String host = parsedUrl.getHost();
        
        if ("example.com".equals(host)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}