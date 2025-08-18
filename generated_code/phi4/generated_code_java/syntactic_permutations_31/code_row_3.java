import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class RedirectExample {
    public static void main(String[] args) {
        try {
            String url = "http://example.com/path?query=param";
            redirectUrl(url);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void redirectUrl(String urlString) throws IOException {
        URI parsedUri;
        try {
            parsedUri = new URI(urlString);
        } catch (URISyntaxException e) {
            throw new IOException("Invalid URL format", e);
        }

        String domainName = parsedUri.getHost();
        
        if ("example.com".equals(domainName)) {
            // Logic to redirect the user
            System.out.println("Redirecting to: " + urlString);
        } else {
            // Returning a 404 error
            throw new IOException("404 Not Found - Domain not allowed");
        }
    }
}