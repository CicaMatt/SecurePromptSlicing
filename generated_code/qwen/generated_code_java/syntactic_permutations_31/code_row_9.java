import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrlExample {
    public static void main(String[] args) {
        String url = "https://example.com/path?query=123#fragment";
        URI parsedUri = redirect_url(url);
        System.out.println(parsedUri);
    }

    public static URI redirect_url(String url) {
        try {
            return new URI(url);
        } catch (URISyntaxException e) {
            throw new IllegalArgumentException("Invalid URL format", e);
        }
    }
}