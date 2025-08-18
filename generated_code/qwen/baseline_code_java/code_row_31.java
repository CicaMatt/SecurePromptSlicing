import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "Redirected to: " + url;
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
        System.out.println(redirect_url("invalidurl"));
    }
}