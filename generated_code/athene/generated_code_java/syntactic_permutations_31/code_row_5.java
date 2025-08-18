import java.net.URL;

public class RedirectHandler {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                // Perform redirection
                System.out.println("Redirecting to: " + url);
            } else {
                // Return 404 error
                System.out.println("Error 404: Not Found");
            }
        } catch (Exception e) {
            System.out.println("Error parsing URL: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com/path");
        handler.redirect_url("http://notexample.com/path");
    }
}