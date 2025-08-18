import java.net.URI;
import javax.servlet.http.HttpServletResponse;

public class UrlRedirector {

    public static void redirectUrl(String url, HttpServletResponse response) {
        try {
            URI parsedUri = new URI(url);
            String host = parsedUri.getHost();
            
            if ("example.com".equals(host)) {
                response.sendRedirect(url);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "404 Not Found");
            }
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Bad Request");
            } catch (Exception ex) {
                // Log or handle the exception as needed
            }
        }
    }

    public static void main(String[] args) {
        // This main method is for testing purposes only.
        // In a real web application, redirectUrl would be called from a servlet.
    }
}