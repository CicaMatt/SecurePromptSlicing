import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        String url = "http://example.com";
        try {
            URI uri = new URI(url);
            System.out.println("Scheme: " + uri.getScheme());
            System.out.println("Host: " + uri.getHost());
            System.out.println("Path: " + uri.getPath());
            System.out.println("Query: " + uri.getQuery());
            
            // Simulate redirection by printing the parsed URL
            redirectUrl(uri);
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL syntax: " + url);
        }
    }

    public static void redirectUrl(URI uri) {
        try {
            URI newUri = new URI(
                uri.getScheme(),
                uri.getUserInfo(),
                uri.getHost(),
                uri.getPort(),
                uri.getPath(),
                uri.getQuery(),
                uri.getFragment()
            );
            
            System.out.println("Redirecting to: " + newUri.toString());
        } catch (URISyntaxException e) {
            System.err.println("Error creating URI for redirection: " + e.getMessage());
        }
    }
}