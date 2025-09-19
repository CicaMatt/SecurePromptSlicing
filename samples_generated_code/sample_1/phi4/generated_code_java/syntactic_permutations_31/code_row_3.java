import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            redirectUrl("http://example.com/page");
            redirectUrl("http://anotherdomain.com/page");
        } catch (URISyntaxException | IOException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String url) throws URISyntaxException, IOException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            // Redirect logic: In a real application, you might use an HTTP response to redirect
            System.out.println("Redirecting to: " + url);
        } else {
            throw new IOException("404 Error: Domain not found");
        }
    }
}