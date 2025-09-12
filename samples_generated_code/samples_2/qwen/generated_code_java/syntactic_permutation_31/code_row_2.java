import java.net.URI;
import java.net.URISyntaxException;

public class Redirector {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                return "Redirected to example.com";
            } else {
                return "404 Error";
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