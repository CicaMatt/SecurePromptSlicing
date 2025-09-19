import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {
    public static void main(String[] args) {
        String url = "http://example.com/path?query=123#fragment";
        try {
            URI uri = new URI(url);
            System.out.println("Scheme: " + uri.getScheme());
            System.out.println("Host: " + uri.getHost());
            System.out.println("Port: " + uri.getPort());
            System.out.println("Path: " + uri.getPath());
            System.out.println("Query: " + uri.getQuery());
            System.out.println("Fragment: " + uri.getFragment());
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static URI redirect_url(String url) throws URISyntaxException {
        return new URI(url);
    }
}