import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("404 Error: Domain not allowed");
            }
        } catch (Exception e) {
            System.out.println("404 Error: Invalid URL");
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com/path");
        handler.redirect_url("http://notexample.com/path");
    }
}