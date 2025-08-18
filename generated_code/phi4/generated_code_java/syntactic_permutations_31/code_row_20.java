import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirect {

    public static String redirectUrl(String urlString) throws URISyntaxException {
        URI uri = new URI(urlString);
        String domainName = uri.getHost();

        if (domainName != null && domainName.endsWith(".")) {
            return "Domain name ends with a dot.";
        }

        // Add your logic here for handling specific domains or redirects
        // For now, returning the same URL as an example
        return urlString;
    }

    public static void main(String[] args) {
        try {
            String url = "http://example.com/";
            System.out.println(redirectUrl(url));
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }
}