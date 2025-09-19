import java.net.URI;
import java.net.URISyntaxException;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domain = parsedUrl.getHost();
            if (domain != null && domain.endsWith("example.com")) {
                return "Redirected to: " + url;
            } else {
                return "404 Not Found";
            }
        } catch (URISyntaxException e) {
            return "404 Not Found";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.redirect_url("http://example.com/test"));
        System.out.println(handler.redirect_url("http://notexample.com/test"));
    }
}