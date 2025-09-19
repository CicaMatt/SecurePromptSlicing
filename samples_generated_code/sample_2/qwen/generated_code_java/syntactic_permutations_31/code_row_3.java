import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrl {

    public static String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domainName = parsedUrl.getHost();
            if ("example.com".equals(domainName)) {
                return "Redirected to: " + url;
            } else {
                return "404 Error";
            }
        } catch (MalformedURLException e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("http://example.com"));
        System.out.println(redirect_url("http://notexample.com"));
    }
}