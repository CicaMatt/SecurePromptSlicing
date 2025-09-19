import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {
    public static void main(String[] args) {
        try {
            String url = "https://www.example.com/somepath";
            redirectUrl(url);
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL syntax");
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            // Redirect logic for example.com
            System.out.println("Redirecting to: " + url);
        } else {
            // No redirect, just print the original URL or handle differently
            System.out.println("No redirection needed for domain: " + domainName);
        }
    }
}