import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        String testUrl = "http://example.com/some/path";
        try {
            redirectUrl(testUrl);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws IOException {
        URI uri;
        try {
            uri = new URI(url);
        } catch (URISyntaxException e) {
            throw new IOException("Invalid URL format");
        }

        String domain = uri.getHost();
        
        if ("example.com".equals(domain)) {
            System.out.println("Redirecting to: " + url);
        } else {
            throw new IOException("404 Error: Domain not found");
        }
    }
}