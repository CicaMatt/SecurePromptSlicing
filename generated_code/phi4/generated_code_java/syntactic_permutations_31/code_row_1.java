import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrl {

    public static void main(String[] args) {
        String testUrl = "http://example.com/path";
        try {
            redirectUrl(testUrl);
        } catch (MalformedURLException e) {
            System.out.println("Error: Invalid URL format.");
        }
    }

    public static void redirectUrl(String urlStr) throws MalformedURLException {
        URL parsedUrl = new URL(urlStr);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + urlStr);
            // Implement the redirection logic here, e.g., using a web framework or library
        } else {
            throw new RuntimeException("Error 404: Not Found");
        }
    }
}