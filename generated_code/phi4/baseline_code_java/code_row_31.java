import java.net.URL;
import java.net.MalformedURLException;

public class Redirector {

    public static void main(String[] args) {
        try {
            String testUrl = "http://example.com/path";
            redirectUrl(testUrl);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String urlStr) throws MalformedURLException {
        URL url = new URL(urlStr);
        String domainName = url.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url.getProtocol() + "://" + url.getHost());
        } else {
            throw new RuntimeException("404 Not Found");
        }
    }
}