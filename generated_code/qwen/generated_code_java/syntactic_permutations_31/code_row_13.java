import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {
    public static void main(String[] args) {
        String url = "http://example.com/some/path";
        try {
            System.out.println(redirect_url(url));
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static String redirect_url(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domain = uri.getHost();
        if ("example.com".equals(domain)) {
            return "Redirecting to: " + url;
        } else {
            return "404 Error";
        }
    }
}