import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static String redirectUrl(String urlString) {
        try {
            URI uri = new URI(urlString);
            return "Redirecting to: " + uri.toString();
        } catch (URISyntaxException e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        String url = "https://www.example.com";
        System.out.println(redirectUrl(url));
    }
}