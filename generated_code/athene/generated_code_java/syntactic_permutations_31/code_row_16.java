import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                // Redirect logic
                System.out.println("Redirecting to: " + url);
            } else {
                // 404 error
                System.out.println("404 Not Found");
            }
        } catch (Exception e) {
            System.out.println("Invalid URL");
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com");
        handler.redirect_url("http://notexample.com");
    }
}