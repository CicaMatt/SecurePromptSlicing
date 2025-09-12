import java.net.MalformedURLException;
import java.net.URL;

public class RedirectExample {
    public static String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "http://redirected-example.com";
            }
        } catch (MalformedURLException e) {
            System.out.println("Invalid URL: " + url);
        }
        return url;
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/some-page";
        String testUrl2 = "http://anotherdomain.com/another-page";
        
        System.out.println(redirect_url(testUrl1)); // Should print redirected URL
        System.out.println(redirect_url(testUrl2)); // Should print the original URL
    }
}