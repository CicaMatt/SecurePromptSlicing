import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                // Perform redirection or further processing
            }
        } catch (Exception e) {
            // Handle exception
        }
    }
}