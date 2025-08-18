import java.net.MalformedURLException;
import java.net.URL;

public class UrlRedirector {

    public static void main(String[] args) {
        String inputUrl = "http://example.com/path/to/resource";
        redirectUrl(inputUrl);
    }

    public static void redirectUrl(String url) {
        try {
            URL parsedUrl = new URL(url);
            String networkLocation = parsedUrl.getHost();
            System.out.println("Network Location: " + networkLocation);
            // Logic to handle redirection based on the network location can be added here
        } catch (MalformedURLException e) {
            System.err.println("The provided string is not a valid URL.");
        }
    }
}