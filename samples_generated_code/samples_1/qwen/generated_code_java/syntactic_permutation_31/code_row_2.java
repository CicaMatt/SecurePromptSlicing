import java.net.MalformedURLException;
import java.net.URL;

public class URLRedirect {

    public static String redirectUrl(String url) {
        try {
            URL parsedUrl = new URL(url);
            String host = parsedUrl.getHost();
            if ("example.com".equals(host)) {
                return "https://redirected.example.com";
            } else {
                return url;
            }
        } catch (MalformedURLException e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirectUrl("http://example.com"));
        System.out.println(redirectUrl("http://anotherdomain.com"));
    }
}