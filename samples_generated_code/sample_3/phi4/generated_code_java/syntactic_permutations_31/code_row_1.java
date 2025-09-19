import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirect {

    public static void main(String[] args) {
        try {
            String url = "http://example.com/path?query=param";
            redirectUrl(url);
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL");
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
        } else {
            System.out.println("404 Error: Domain not found");
        }
    }
}