import java.net.URI;
import java.net.URISyntaxException;

public class RedirectChecker {

    public static void main(String[] args) {
        String url = "http://example.com/path";
        System.out.println(redirect_url(url));
    }

    public static boolean redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            return "example.com".equals(domainName);
        } catch (URISyntaxException e) {
            e.printStackTrace();
            return false;
        }
    }
}