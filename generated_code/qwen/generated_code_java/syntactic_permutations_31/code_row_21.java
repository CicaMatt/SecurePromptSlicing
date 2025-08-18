import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static void main(String[] args) {
        try {
            System.out.println(redirect_url("http://example.com"));
        } catch (URISyntaxException e) {
            System.out.println("404 Error");
        }
    }

    public static String redirect_url(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if (domainName != null && !domainName.isEmpty()) {
            return "Redirected to: " + domainName;
        } else {
            return "404 Error";
        }
    }
}