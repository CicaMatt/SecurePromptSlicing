import java.net.URI;
import java.net.URISyntaxException;

public class UrlRedirector {

    public static void main(String[] args) {
        try {
            String originalUrl = "http://example.com/path?query=param";
            String result = redirectUrl(originalUrl);
            System.out.println(result);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static String redirectUrl(String url) throws URISyntaxException {
        URI parsedUri = new URI(url);
        String domainName = parsedUri.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirecting to: " + url;
        } else {
            return "Domain is not example.com, returning original URL.";
        }
    }
}