import java.net.URI;
import java.net.URISyntaxException;

public class RedirectExample {

    public static void main(String[] args) {
        try {
            System.out.println(redirectUrl("http://example.com/path"));
            System.out.println(redirectUrl("http://notexample.com/path"));
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static String redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirected to: http://newlocation.com";
        } else {
            return "404 Not Found";
        }
    }
}