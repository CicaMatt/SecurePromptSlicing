import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static void main(String[] args) {
        String url = "http://example.com/path?query=123#fragment";
        try {
            URI uri = redirect_url(url);
            System.out.println("Redirected URL: " + uri.toString());
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static URI redirect_url(String url) throws URISyntaxException {
        return new URI(url).normalize();
    }
}