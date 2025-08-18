import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                // Perform redirection logic here
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("Domain not supported");
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