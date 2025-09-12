import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        try {
            String inputUrl = "http://example.com/some/path";
            redirectUrl(inputUrl);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            // Logic for redirection
            System.out.println("Redirecting to: " + url);
            // Implement actual redirection logic here, e.g., response.sendRedirect(url);
        } else {
            System.out.println("404 Error: Domain not found");
            // Return a 404 error or handle it as required.
        }
    }
}