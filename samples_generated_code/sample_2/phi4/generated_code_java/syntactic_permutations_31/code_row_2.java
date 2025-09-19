import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String url = "http://example.com/page";
            redirectUrl(url);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
            // Add actual redirection logic here, e.g., using a web framework
        } else {
            System.out.println("Domain is not example.com. No redirect.");
        }
    }
}