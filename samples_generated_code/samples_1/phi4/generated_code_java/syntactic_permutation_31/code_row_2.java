import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        String url = "https://example.com/path";
        redirectUrl(url);
    }

    public static void redirectUrl(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();

            if (domainName != null && "example.com".equals(domainName)) {
                // Redirect logic here
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("Not redirecting. Domain is not example.com");
            }
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL syntax.");
        }
    }
}