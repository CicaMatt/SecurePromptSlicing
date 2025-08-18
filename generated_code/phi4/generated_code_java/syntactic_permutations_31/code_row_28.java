import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String url = "http://example.com/some/path";
            redirectUrl(url);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException {
        URI parsedUrl = new URI(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
            // Add your redirection logic here
            // For example, you might call a method that handles the redirect
        } else {
            System.out.println("Domain is not example.com. No redirection.");
        }
    }
}