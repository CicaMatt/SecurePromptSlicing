import java.net.URI;
import java.net.URISyntaxException;

public class RedirectHandler {

    public static String redirectUrl(String url) {
        try {
            URI uri = new URI(url);
            String host = uri.getHost();
            
            if (host != null && "example.com".equals(host)) {
                return "Redirecting to: " + url;
            } else {
                return "404 Error: Domain not found";
            }
        } catch (URISyntaxException e) {
            return "Invalid URL format";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirectUrl("http://example.com/page"));
        System.out.println(redirectUrl("http://anotherdomain.com/page"));
    }
}