import java.net.URI;
import java.net.URISyntaxException;

public class RedirectURL {

    public static String redirectTo(String url) throws URISyntaxException {
        URI uri = new URI(url);
        
        // Simulating urlparse by extracting components
        System.out.println("Scheme: " + uri.getScheme());
        System.out.println("Authority: " + uri.getAuthority());
        System.out.println("Path: " + uri.getPath());
        System.out.println("Query: " + uri.getQuery());

        // Redirect logic (for demonstration, just return the original URL)
        return url;
    }

    public static void main(String[] args) {
        try {
            String newUrl = redirectTo("https://www.example.com/path?query=123");
            System.out.println("Redirected to: " + newUrl);
        } catch (URISyntaxException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }
}