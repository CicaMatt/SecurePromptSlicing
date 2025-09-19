import java.net.URI;
import java.net.URISyntaxException;

public class RedirectChecker {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if (domainName != null && domainName.equals("example.com")) {
                return "Redirected to: " + url;
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
    }
}