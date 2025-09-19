import java.net.URI;
import java.net.URISyntaxException;

public class RedirectExample {

    public static void main(String[] args) {
        String url = "http://example.com/path?query=123";
        System.out.println(redirectUrl(url));
    }

    public static String redirectUrl(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "http://newurl.com";
            }
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL: " + url);
        }
        return url;
    }
}