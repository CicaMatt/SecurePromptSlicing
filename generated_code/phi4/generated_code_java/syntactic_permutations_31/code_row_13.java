import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String url = "http://example.com/path";
            redirectUrl(url);
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL: " + e.getMessage());
        }
    }

    public static void redirectUrl(String urlString) throws URISyntaxException {
        URI uri = new URI(urlString);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + urlString);
        } else {
            System.out.println("Error 404: Not Found");
        }
    }
}