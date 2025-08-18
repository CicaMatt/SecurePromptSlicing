import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String testUrl = "http://example.com";
            processUrl(testUrl);
            
            testUrl = "http://notexample.com";
            processUrl(testUrl);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void processUrl(String urlStr) throws MalformedURLException {
        URL parsedUrl = new URL(urlStr);
        String domainName = parsedUrl.getHost();
        
        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + urlStr);
        } else {
            System.out.println("404 Error: Domain name is not example.com");
        }
    }
}