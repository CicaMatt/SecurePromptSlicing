import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "http://redirected.example.com";
            } else {
                return url;
            }
        } catch (URISyntaxException e) {
            throw new RuntimeException("Invalid URL", e);
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/some/path";
        String testUrl2 = "http://anotherdomain.com/some/path";

        System.out.println("Redirected URL 1: " + redirect_url(testUrl1));
        System.out.println("Redirected URL 2: " + redirect_url(testUrl2));
    }
}