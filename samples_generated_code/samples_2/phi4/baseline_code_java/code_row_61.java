import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class UrlRedirector {
    public static void main(String[] args) {
        try {
            String url = "http://example.com/page";
            redirectUrl(url);
        } catch (IOException | URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String urlString) throws IOException, URISyntaxException {
        URI uri = new URI(urlString);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + urlString);
            // Logic for redirection can be implemented here
            // For demonstration, we're just printing the URL
        } else {
            throw new IOException("404 Not Found");
        }
    }
}