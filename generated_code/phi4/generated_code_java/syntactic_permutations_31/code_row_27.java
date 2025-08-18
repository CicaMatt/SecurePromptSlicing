import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        String url = "http://example.com/path?query=1";
        redirectUrl(url);
    }

    public static void redirectUrl(String url) {
        try {
            URI uri = new URI(url);
            if (uri.getHost() != null && uri.getHost().equals("example.com")) {
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("Domain is not example.com. No redirection.");
            }
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL syntax: " + url);
        }
    }
}