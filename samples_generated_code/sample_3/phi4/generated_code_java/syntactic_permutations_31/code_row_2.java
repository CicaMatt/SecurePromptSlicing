import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {
    public static void main(String[] args) {
        String testUrl = "http://example.com/some/path";
        redirectUrl(testUrl);
        
        String nonExampleUrl = "http://anotherdomain.com/otherpath";
        redirectUrl(nonExampleUrl);
    }

    public static void redirectUrl(String url) {
        try {
            URI uri = new URI(url);
            String domainName = uri.getHost();

            if (domainName != null && domainName.equals("example.com")) {
                System.out.println("Redirecting to: " + url);
                // Redirect logic here
            } else {
                System.out.println("Domain is not example.com. No redirect.");
                // Handle non-example domains here
            }
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL format: " + url);
        }
    }
}