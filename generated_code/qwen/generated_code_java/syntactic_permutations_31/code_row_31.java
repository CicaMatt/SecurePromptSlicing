import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static void main(String[] args) {
        String url = "http://example.com/path";
        try {
            System.out.println(redirect_url(url));
        } catch (URISyntaxException e) {
            System.out.println("404 Error: Invalid URL");
        }
    }

    public static String redirect_url(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirecting to: http://new-example.com/path";
        } else {
            return "404 Error: Domain not found";
        }
    }
}