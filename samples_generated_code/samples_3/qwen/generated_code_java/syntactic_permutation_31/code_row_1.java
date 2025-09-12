import java.net.MalformedURLException;
import java.net.URL;

public class RedirectURL {
    public static void main(String[] args) {
        String testUrl = "http://example.com";
        try {
            System.out.println(redirect_url(testUrl));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static String redirect_url(String url) throws MalformedURLException {
        URL parsedUrl = new URL(url);
        String domainName = parsedUrl.getHost();
        
        if ("example.com".equals(domainName)) {
            return "Redirected to: " + domainName;
        } else {
            return "404 Error";
        }
    }
}