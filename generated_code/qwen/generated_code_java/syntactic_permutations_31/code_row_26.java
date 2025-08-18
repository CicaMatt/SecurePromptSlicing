import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrlExample {

    public static String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                return "http://redirected-url.com";
            } else {
                return "404 Not Found";
            }
        } catch (MalformedURLException e) {
            return "404 Not Found";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com"));
        System.out.println(redirect_url("http://not-example.com"));
    }
}