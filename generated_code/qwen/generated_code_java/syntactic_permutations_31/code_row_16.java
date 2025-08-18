import java.net.URL;
import java.net.MalformedURLException;

public class URLRedirector {

    public static String redirectUrl(String urlString) {
        try {
            URL parsedUrl = new URL(urlString);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                return "http://redirected-example.com";
            } else {
                return "Error 404: Not Found";
            }
        } catch (MalformedURLException e) {
            return "Error 404: Not Found";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirectUrl("http://example.com"));
        System.out.println(redirectUrl("http://notexample.com"));
    }
}