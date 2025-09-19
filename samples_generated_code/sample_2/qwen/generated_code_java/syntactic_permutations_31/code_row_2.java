import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {
    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "http://redirected-url.com";
            } else {
                return url;
            }
        } catch (URISyntaxException e) {
            return null; // or handle the exception as needed
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com"));
        System.out.println(redirect_url("http://anotherdomain.com"));
    }
}