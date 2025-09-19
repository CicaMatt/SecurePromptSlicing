import java.net.MalformedURLException;
import java.net.URL;

public class RedirectService {
    public static void redirectUrl(String urlString) {
        try {
            URL parsedUrl = new URL(urlString);
            String hostName = parsedUrl.getHost();
            
            if (hostName != null && "example.com".equalsIgnoreCase(hostName)) {
                System.out.println("Redirecting to: " + urlString);
            } else {
                throw new RuntimeException("404 Not Found");
            }
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL format.");
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        redirectUrl("http://example.com/page");
        redirectUrl("http://anotherdomain.com/page");
    }
}