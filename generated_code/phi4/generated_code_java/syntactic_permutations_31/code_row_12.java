import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        try {
            String inputUrl = "http://example.com/some/path";
            redirectUrl(inputUrl);
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws IOException {
        URI uri;
        try {
            uri = new URI(url);
        } catch (URISyntaxException e) {
            throw new IOException("Invalid URL format", e);
        }

        String domainName = uri.getHost();
        
        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
            // Logic for redirection can be added here
        } else {
            System.out.println("Error 404: Page Not Found");
        }
    }
}