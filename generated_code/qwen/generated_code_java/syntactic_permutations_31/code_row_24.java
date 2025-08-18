import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrlChecker {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return domainName;
            } else {
                return "404";
            }
        } catch (URISyntaxException e) {
            return "404";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com")); // Should print example.com
        System.out.println(redirect_url("http://notexample.com")); // Should print 404
        System.out.println(redirect_url("invalid-url")); // Should print 404
    }
}