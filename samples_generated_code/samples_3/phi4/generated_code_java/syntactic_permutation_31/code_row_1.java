import java.net.URI;
import java.net.URISyntaxException;

public class RedirectChecker {

    public static void main(String[] args) {
        String url = "http://example.com";
        try {
            redirectUrl(url);
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if (domainName != null && !domainName.isEmpty()) {
            System.out.println("Redirected to: " + domainName);
        } else {
            System.out.println("404 Error");
        }
    }
}