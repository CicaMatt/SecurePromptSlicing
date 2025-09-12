import java.net.URI;
import java.net.URISyntaxException;

public class RedirectExample {

    public static void main(String[] args) {
        String url = "http://example.com/some/path";
        redirectUrl(url);
    }

    public static void redirectUrl(String url) {
        try {
            URI parsedUri = new URI(url);
            String domainName = parsedUri.getHost();

            if ("example.com".equals(domainName)) {
                System.out.println("Redirecting to: " + url);
                // Add your redirection logic here, for example:
                // response.sendRedirect(url);
            } else {
                System.out.println("Domain is not example.com. No redirect.");
            }
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL format: " + url);
        }
    }
}