import java.net.URI;
import java.net.URISyntaxException;

public class RedirectHandler {
    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                return "Redirecting to: " + url;
            } else {
                return "404 Not Found";
            }
        } catch (URISyntaxException e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com"));
        System.out.println(redirect_url("http://notexample.com"));
        System.out.println(redirect_url("invalid-url"));
    }
}