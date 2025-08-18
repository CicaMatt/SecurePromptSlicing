import java.net.URI;
import java.net.URISyntaxException;

public class RedirectChecker {

    public static void main(String[] args) {
        String urlString = "http://example.com";
        try {
            System.out.println(redirectUrl(urlString));
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL: " + e.getMessage());
        }
    }

    public static String redirectUrl(String url) throws URISyntaxException {
        URI parsedUri = new URI(url);
        String domainName = parsedUri.getHost();
        
        if (domainName != null && !domainName.isEmpty()) {
            return "Redirected to: " + domainName;
        } else {
            return "404 error";
        }
    }
}