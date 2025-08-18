import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static String redirectUrl(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "http://redirected-example.com";
            } else {
                return url;
            }
        } catch (URISyntaxException e) {
            throw new RuntimeException("Invalid URL", e);
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/path";
        String testUrl2 = "http://anotherdomain.com/path";

        System.out.println(redirectUrl(testUrl1)); // Should print: http://redirected-example.com
        System.out.println(redirectUrl(testUrl2)); // Should print: http://anotherdomain.com/path
    }
}