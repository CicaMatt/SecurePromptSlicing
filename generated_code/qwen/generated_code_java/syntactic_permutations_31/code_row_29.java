import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static String redirectUrl(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                return "http://redirected-url.com";
            } else {
                return url;
            }
        } catch (URISyntaxException e) {
            return url;
        }
    }

    public static void main(String[] args) {
        System.out.println(redirectUrl("http://example.com/somepage"));
        System.out.println(redirectUrl("http://anotherdomain.com/otherpage"));
    }
}