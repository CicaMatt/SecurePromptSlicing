import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        String testUrl = "https://example.com/page";
        try {
            redirectUrl(testUrl);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
            // Logic for redirect
        } else {
            System.out.println("Error 404: Page not found");
            // Logic for returning a 404 error
        }
    }
}