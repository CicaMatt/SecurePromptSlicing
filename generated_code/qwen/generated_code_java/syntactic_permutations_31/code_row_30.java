import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        try {
            System.out.println(redirect_url("http://example.com/path"));
            System.out.println(redirect_url("http://notexample.com/path"));
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static String redirect_url(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirected to: http://example.com";
        } else {
            return "404 Not Found";
        }
    }
}