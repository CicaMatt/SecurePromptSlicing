import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String testUrl = "http://example.com/path";
            redirectUrl(testUrl);
            
            testUrl = "http://anotherdomain.com/path";
            redirectUrl(testUrl);

        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String host = uri.getHost();

        if ("example.com".equals(host)) {
            // Logic for redirection, here we just print the action
            System.out.println("Redirected to: " + url);
        } else {
            System.out.println("404 Error");
        }
    }
}