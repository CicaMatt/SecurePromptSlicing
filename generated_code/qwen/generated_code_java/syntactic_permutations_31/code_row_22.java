import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static void main(String[] args) {
        String url = "http://example.com/path?query=123";
        System.out.println(redirect_url(url));
    }

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                // You can modify the redirection logic here
                return "http://newdomain.com";
            }
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
        return url;
    }
}