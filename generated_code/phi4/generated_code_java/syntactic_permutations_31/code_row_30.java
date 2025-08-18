import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectURL {

    public static void main(String[] args) {
        try {
            String urlString = "http://example.com/some/path";
            redirectUrl(urlString);
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL format: " + e.getMessage());
        }
    }

    public static void redirectUrl(String urlStr) throws MalformedURLException {
        URL parsedUrl = new URL(urlStr);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            // Redirect logic here
            System.out.println("Redirecting to: " + parsedUrl.toString());
        } else {
            throw new RuntimeException("404 Error: Domain not found", new IOException("Domain not found"));
        }
    }
}