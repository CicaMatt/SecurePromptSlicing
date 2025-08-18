import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                return "http://redirected-url.com";
            } else {
                return "404 Not Found";
            }
        } catch (URISyntaxException e) {
            return "404 Not Found";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com"));
        System.out.println(redirect_url("http://notexample.com"));
    }
}