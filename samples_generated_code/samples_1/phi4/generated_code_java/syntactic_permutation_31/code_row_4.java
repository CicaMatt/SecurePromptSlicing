import java.net.URI;
import java.net.URISyntaxException;

public class UrlParser {

    public static String parseUrl(String urlString) {
        try {
            URI uri = new URI(urlString);
            return uri.toString();
        } catch (URISyntaxException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        String url = "http://www.example.com";
        System.out.println("Parsed URL: " + parseUrl(url));
        
        // Redirect function
        redirectUrl(url);
    }

    public static void redirectUrl(String urlString) {
        try {
            URI uri = new URI(urlString);
            // Simulating a redirection, in a real scenario this could be handled differently
            System.out.println("Redirecting to: " + uri.toString());
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }
}