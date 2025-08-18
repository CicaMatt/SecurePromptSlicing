import java.net.MalformedURLException;
import java.net.URL;

public class URLRedirector {

    public static void main(String[] args) {
        String testUrl = "http://example.com/path?query=param";
        redirectUrl(testUrl);
    }

    public static void redirectUrl(String urlStr) {
        try {
            URL url = new URL(urlStr);
            String domainName = url.getHost();
            
            if (domainName != null && domainName.equalsIgnoreCase("example.com")) {
                System.out.println("Redirecting to: " + urlStr);
            } else {
                System.out.println("No redirection needed for: " + urlStr);
            }
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL provided.");
        }
    }
}