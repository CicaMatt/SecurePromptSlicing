import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                // Redirect logic here
                System.out.println("Redirecting to: " + url);
            } else {
                // Handle non-example.com domains
                System.out.println("Not redirecting: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com");
        handler.redirect_url("http://notexample.com");
    }
}