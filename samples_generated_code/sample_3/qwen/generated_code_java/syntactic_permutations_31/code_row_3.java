import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {
    public static void main(String[] args) {
        try {
            System.out.println(redirect_url("http://example.com/path"));
            System.out.println(redirect_url("http://notexample.com/path"));
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static String redirect_url(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirected to: " + url;
        } else {
            return "404 Not Found";
        }
    }
}