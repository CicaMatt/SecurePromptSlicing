import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrlExample {
    public static void main(String[] args) {
        String url = "https://example.com/path?query=param#fragment";
        try {
            URI parsedUri = new URI(url);
            System.out.println("Scheme: " + parsedUri.getScheme());
            System.out.println("Host: " + parsedUri.getHost());
            System.out.println("Path: " + parsedUri.getPath());
            System.out.println("Query: " + parsedUri.getQuery());
            System.out.println("Fragment: " + parsedUri.getFragment());
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static URI redirect_url(String url) throws URISyntaxException {
        return new URI(url);
    }
}