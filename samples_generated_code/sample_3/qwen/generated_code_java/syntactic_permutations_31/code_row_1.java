import java.net.MalformedURLException;
import java.net.URL;

public class RedirectHandler {
    public static void main(String[] args) {
        try {
            System.out.println(redirectUrl("http://example.com/path"));
            System.out.println(redirectUrl("http://notexample.com/path"));
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL: " + e.getMessage());
        }
    }

    public static String redirectUrl(String url) throws MalformedURLException {
        URL parsedUrl = new URL(url);
        String domain = parsedUrl.getHost();
        
        if ("example.com".equals(domain)) {
            return "Redirecting to: " + url;
        } else {
            return "404 Error: Domain not found";
        }
    }
}