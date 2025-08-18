import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                // Simulate redirection by printing the target URL
                System.out.println("Redirecting to: " + url);
            }
        } catch (Exception e) {
            // Handle malformed URLs or other exceptions
            System.err.println("Invalid URL: " + url);
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com/path");
    }
}