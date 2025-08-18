import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class UrlRedirector {

    public static void main(String[] args) {
        try {
            String inputUrl = "https://example.com/path";
            redirectUrl(inputUrl);
        } catch (MalformedURLException e) {
            System.out.println("Invalid URL format.");
        }
    }

    public static void redirectUrl(String urlStr) throws MalformedURLException {
        URL url = new URL(urlStr);
        String domainName = url.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + urlStr);
            // Redirect logic can be implemented here
        } else {
            throw new IOException("404 Not Found");
        }
    }
}