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
                // 404 error response
                System.out.println("Error 404: Not Found");
            }
        } catch (Exception e) {
            // Handle malformed URL or other exceptions
            System.out.println("Error 404: Not Found");
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        handler.redirect_url("http://example.com/path");
        handler.redirect_url("http://notexample.com/path");
    }
}