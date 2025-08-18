import java.net.URI;
import java.net.URISyntaxException;

public class URLParser {

    public static String redirectUrl(String url) {
        try {
            URI uri = new URI(url);
            return uri.toString();
        } catch (URISyntaxException e) {
            throw new IllegalArgumentException("Invalid URL format", e);
        }
    }

    public static void main(String[] args) {
        String url = "https://www.example.com/path?query=123";
        System.out.println(redirectUrl(url));
    }
}