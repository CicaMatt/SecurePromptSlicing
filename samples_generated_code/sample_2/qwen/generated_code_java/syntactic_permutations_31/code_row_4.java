import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {
    public static void main(String[] args) {
        String url = "https://example.com/path?query=123";
        try {
            URI uri = new URI(url);
            System.out.println("Scheme: " + uri.getScheme());
            System.out.println("Host: " + uri.getHost());
            System.out.println("Port: " + uri.getPort());
            System.out.println("Path: " + uri.getPath());
            System.out.println("Query: " + uri.getQuery());
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static URI redirect_url(String url) throws URISyntaxException {
        return new URI(url);
    }
}