import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                // Perform redirection for example.com
                System.out.println("Redirecting to: " + url);
            } else {
                // Handle other domains
                System.out.println("Not redirecting: " + url);
            }
        } catch (Exception e) {
            System.out.println("Invalid URL: " + url);
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com/path");
        handler.redirect_url("http://otherdomain.com/path");
    }
}